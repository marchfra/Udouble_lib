//
// Created by Francesco Marchisotti  on 20/11/21.
//

#ifndef UDOUBLE_UDOUBLE_H
#define UDOUBLE_UDOUBLE_H


double round(const double &value, const int &digits);

double sqr_sum(const double &x, const double &y);


class Udouble {
public:
	Udouble() = default;
	Udouble(double n, double s = 0.);

	double getN() const;
	void setN(double n);
	double getS() const;
	void setS(double s);

	friend std::ostream &operator<<(std::ostream &out, const Udouble &u);
	friend std::istream &operator>>(std::istream &in, Udouble &u);

	Udouble operator+(const Udouble &u) const;
	Udouble operator-(const Udouble &u) const;
	Udouble operator*(const Udouble &u) const;
	Udouble operator/(const Udouble &u) const;
	// I should define comparison between Udouble and double as well
	bool operator<(const Udouble &u) const;
	bool operator>(const Udouble &u) const;
	bool operator<=(const Udouble &u) const;
	bool operator>=(const Udouble &u) const;
	bool operator==(const Udouble &u) const;
	bool operator!=(const Udouble &u) const;


	static void format(std::ostream &out, double &nom_val, double &std_dev);
private:
	double nominal_value;

	double std_dev;

	static int PDG_precision(double &std_dev);

	static int first_digit(double value);

	static int signif_dgt_to_limit(double value, int signifD);

	static char sign(int x);
};


#endif //UDOUBLE_UDOUBLE_H
