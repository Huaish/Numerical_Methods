#include <iostream>
#include <cmath>
using namespace std;

double g(double x)
{
    return pow((2 * x + 2), 1.0 / 3.0);
}

double g_plus(double x)
{
    return (2.0 / 3.0) * pow((2 * x + 2), -2.0 / 3.0);
}

double FPI(double x0, double (*g)(double))
{
    double x1 = g(x0);
    int cnt = 1e6;
    while (abs(x1 - x0) > 1e-6 && cnt--)
    {
        x0 = x1;
        x1 = g(x0);
    }

    if (cnt <= 0)
    {
        cout << "FPI failed" << endl;
    }

    return x1;
}

int main()
{
    // fpi function
    // x = g(x)
    // x^3 = 2x + 2
    // g(x) = (2x + 2)^(1/3)
    // g'(x) = (2/3)(2x + 2)^(-2/3)
    // |g'(r)| < 1 => convergence

    double r = FPI(0.5, g);

    cout << r << endl;
    cout << abs(g_plus(r)) << endl;

    return 0;
}