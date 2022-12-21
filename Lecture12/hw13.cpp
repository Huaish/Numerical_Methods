#include <cmath>
#include <iostream>
using namespace std;

// double f(double x) { return x * x; }

// double df(double x) { return 2 * x; }

double f(double x) { return pow(x, 4) - 2 * pow(x, 3) + 2; }

double df(double x) { return 4 * pow(x, 3) - 6 * pow(x, 2); }

int main()
{
    double step = 0.2;
    double x1 = 0, x2 = 1;

    while (abs(x2 - x1) >= 10e-7) {
        x1 = x2;
        x2 = x1 - step * df(x1);
    }
    cout << x1 << endl;
    return 0;
}