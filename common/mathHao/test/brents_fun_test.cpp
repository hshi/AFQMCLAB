#include "../include/brents_fun.h"
#include "../../testHao/gtest_custom.h"

using namespace std;

double fun1(double x)
{
  return -2.0*x+1;
}

double fun2(double x)
{
  return x*x-2.0*x-3;
}

double fun3(double x,double y)
{
  return x*x-2.0*x-1.0-y;
}

TEST (brent, linear_x)
{
    double eta=1e-15;
    double x;
    brentRootFinding(fun1, x, -1.0, 5.0, eta);

    EXPECT_DOUBLE_EQ (0.5, x);
}

TEST (brent, quadratic_x)
{
    double eta=1e-15;
    double x;
    brentRootFinding(fun2, x, 1.0, 5.0, eta);

    EXPECT_DOUBLE_EQ (3.0, x);
}

TEST (brent, quadratic_x_y)
{
    double eta=1e-15;
    double x;
    brentRootFinding([](double x)
                     { return fun3(x, 7.0); }, x, 0.0, 5.0, eta);
    EXPECT_DOUBLE_EQ (4.0, x);

    brentRootFinding(bind(fun3, placeholders::_1, 7.0), x, 0.0, 5.0, eta);
    EXPECT_DOUBLE_EQ (4.0, x);
}