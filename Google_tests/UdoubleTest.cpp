//
// Created by Francesco Marchisotti  on 20/11/21.
//

#include <gtest/gtest.h>
#include <cmath>
#include <random>
#include "../Udouble.h"

class UdoubleTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		x = new Udouble();
		y = new Udouble();
	}

	virtual void TearDown() {
		delete x;
		delete y;
	}

	Udouble *x;
	Udouble *y;
};

TEST_F(UdoubleTest, sum) {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(-1000, 1000);
	int num_tests = 100;
	double nx = distr(eng), ny = distr(eng);
	double sx = distr(eng), sy = distr(eng);
	x->setN(nx);
	x->setS(sx);
	y->setN(ny);
	y->setS(sy);
	Udouble sum = *x + *y;
	ASSERT_DOUBLE_EQ(sum.getN(), nx + ny);
	ASSERT_DOUBLE_EQ(sum.getS(), sqrt(sx * sx + sy * sy));
}

TEST_F(UdoubleTest, difference) {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(-1000, 1000);
	int num_tests = 100;
	double nx = distr(eng), ny = distr(eng);
	double sx = distr(eng), sy = distr(eng);
	x->setN(nx);
	x->setS(sx);
	y->setN(ny);
	y->setS(sy);
	Udouble diff = *x - *y;
	ASSERT_DOUBLE_EQ(diff.getN(), nx - ny);
	ASSERT_DOUBLE_EQ(diff.getS(), sqrt(sx * sx + sy * sy));
}

TEST_F(UdoubleTest, multiplication) {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(-1000, 1000);
	double nx = distr(eng), ny = distr(eng);
	double sx = distr(eng), sy = distr(eng);
	x->setN(nx);
	x->setS(sx);
	y->setN(ny);
	y->setS(sy);
	Udouble mult = *x * *y;
	ASSERT_DOUBLE_EQ(mult.getN(), nx * ny);
	if (nx == 0 || ny == 0) {
		ASSERT_TRUE(std::isnan(mult.getS()));
	} else {
		ASSERT_DOUBLE_EQ(mult.getS(), nx * ny * sqrt(sx / nx * sx / nx + sy / ny * sy / ny));
	}
}

TEST_F(UdoubleTest, division) {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(-1000, 1000);
	double nx = distr(eng), ny = distr(eng);
	double sx = distr(eng), sy = distr(eng);
	x->setN(nx);
	x->setS(sx);
	y->setN(ny);
	y->setS(sy);
	Udouble div = *x / *y;
	ASSERT_DOUBLE_EQ(div.getN(), nx / ny);
	ASSERT_DOUBLE_EQ(div.getS(), nx / ny * sqrt(sx / nx * sx / nx + sy / ny * sy / ny));
}