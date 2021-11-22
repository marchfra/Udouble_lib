//
// Created by Francesco Marchisotti  on 20/11/21.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include "Udouble.h"

double round(const double &value, const int &digits) {
	double factor = pow(10, digits);
	return round(value * factor) / factor;
}

double sqr_sum(const double &x, const double &y) {
	return sqrt(x * x + y * y);
}

std::ostream &operator<<(std::ostream &out, const Udouble &u) {
	double nominal_value = u.nominal_value;
	double std_dev = u.std_dev;
	Udouble::format(out, nominal_value, std_dev);
	return out;
}

std::istream &operator>>(std::istream &in, Udouble &u) {
	std::cout << "Nominal value: ";
	in >> u.nominal_value;
	std::cout << "Standard deviation: ";
	in >> u.std_dev;
	return in;
}

Udouble Udouble::operator+(const Udouble &u) const {
	double nominal = nominal_value + u.nominal_value;
	double sigma = sqr_sum(std_dev, u.std_dev);
	return {nominal, sigma};
}

Udouble Udouble::operator-(const Udouble &u) const {
	double nominal = nominal_value - u.nominal_value;
	double sigma = sqr_sum(std_dev, u.std_dev);
	return {nominal, sigma};
}

Udouble Udouble::operator*(const Udouble &u) const {
	double nominal = nominal_value * u.nominal_value;
	double sigma_rel = sqrt(std_dev / nominal_value * std_dev / nominal_value +
							u.std_dev / u.nominal_value * u.std_dev / u.nominal_value);
	return {nominal, nominal * sigma_rel};
}

Udouble Udouble::operator/(const Udouble &u) const {
	double nominal = nominal_value / u.nominal_value;
	double sigma_rel = sqrt(std_dev / nominal_value * std_dev / nominal_value +
							u.std_dev / u.nominal_value * u.std_dev / u.nominal_value);
	return {nominal, nominal * sigma_rel};
}

bool Udouble::operator<(const Udouble &u) const {
	return nominal_value < u.nominal_value;
}

bool Udouble::operator>(const Udouble &u) const {
	return nominal_value > u.nominal_value;
}

bool Udouble::operator>=(const Udouble &u) const {
	return nominal_value >= u.nominal_value;
}

bool Udouble::operator<=(const Udouble &u) const {
	return nominal_value <= u.nominal_value;
}

bool Udouble::operator==(const Udouble &u) const {
	return nominal_value == u.nominal_value and std_dev == u.std_dev;
}

bool Udouble::operator!=(const Udouble &u) const {
	return nominal_value != u.nominal_value and std_dev != u.std_dev;
}

Udouble::Udouble(double n, double s) : nominal_value(n), std_dev(s) {
	Udouble::nominal_value = n;
	Udouble::std_dev = s;
}

double Udouble::getN() const {
	return nominal_value;
}

void Udouble::setN(double n) {
	Udouble::nominal_value = n;
}

double Udouble::getS() const {
	return std_dev;
}

void Udouble::setS(double s) {
	Udouble::std_dev = s;
}

void Udouble::format(std::ostream &out, double &nom_val, double &std_dev) {
	double exp_ref_value = std::max(nom_val, std_dev);  // the value to reference when choosing the exponent for
														// scientific notation
	int num_signif_d = PDG_precision(std_dev);  // return the number of significative digits to keep in the error
	int digits_limit = signif_dgt_to_limit(std_dev, num_signif_d);  // the position of the last digit of the error
	int common_exp = first_digit(round(exp_ref_value, -digits_limit));  // the exponent
	double factor = pow(10, common_exp);
	double nom_val_mantissa = nom_val / factor;
	double std_dev_mantissa = std_dev / factor;
	int signif_limit = digits_limit - common_exp;
	int prec = std::max(-signif_limit, 1);
	out << "(" << std::fixed << std::setprecision(prec) << nom_val_mantissa;
	out << "+/-" << std::round(std_dev_mantissa * pow(10, prec)) / pow(10, prec);
	out << ")e" << sign(common_exp) << std::setfill('0') << std::setw(2) << std::abs(common_exp) << std::endl;
}

int Udouble::PDG_precision(double &std_dev) {
	int exponent = first_digit(std_dev);
	int factor;
	if (exponent >= 0) {
		exponent -= 2;
		factor = 1;
	} else {
		exponent += 1;
		factor = 1000;
	}
	auto digits = (int)(std_dev / pow(10, exponent) * factor);

	// Rules
	if (digits <= 354) {
		return 2;
	} else if (digits <= 949) {
		return 1;
	} else {
		std_dev = pow(10, exponent) * (1000. / factor);
		return 2;
	}
}

int Udouble::first_digit(double value) {
	if (value == 0) {
		return 0;
	} else {
		return (int)floor(log10(abs(value)));
	}
}

int Udouble::signif_dgt_to_limit(double value, int num_signif_d) {
	int fst_digit = first_digit(value);
	int limit_no_rounding = fst_digit - num_signif_d + 1;
	double rounded = round(value, -limit_no_rounding);
	int fst_digit_rounded = first_digit(rounded);

	if (fst_digit_rounded > fst_digit) {
		limit_no_rounding += 1;
	}

	return limit_no_rounding;
}

char Udouble::sign(int x) {
	if (x >= 0) {
		return '+';
	} else {
		return '-';
	}
}
