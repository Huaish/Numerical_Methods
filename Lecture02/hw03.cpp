#include <iostream>
#include <cmath>
using namespace std;

double f1(double x)
{
    return pow(x, 5) + x - 1;
}

double f1_plus(double x)
{
    return 5 * pow(x, 4) + 1;
}

double f2(double x)
{
    // f(x) = lnx + x^2 - 3
    return log(x) + pow(x, 2) - 3;
}

double f2_plus(double x)
{
    return 1 / x + 2 * x;
}

double f3(double x)
{
    return sin(x) - 6 * x - 5;
}

double f3_plus(double x)
{
    return cos(x) - 6;
}

double Newton(double x0, double (*f)(double), double (*f_plus)(double))
{
    double x1 = x0 - f(x0) / f_plus(x0);
    while (abs(x1 - x0) > 0.000001)
    {
        x0 = x1;
        x1 = x0 - f(x0) / f_plus(x0);
    }
    return x1;
}

int main()
{
    // Newton's Iteration
    // x_i+1 = x_i - f(x_i) / f'(x_i)

    // g(x) = x0 - f(x0) / f'(x0)
    // x1 = x0 - f(x0) / f'(x0)

    double r = 0.5;

    cout << Newton(r, f1, f1_plus) << endl;
    cout << Newton(r, f2, f2_plus) << endl;
    cout << Newton(r, f3, f3_plus) << endl;

    return 0;
}
