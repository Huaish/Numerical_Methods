/*
Bisection method
Method for finding a root of a scalar equation f(x) = 0 in an interval [a, b]
Assumption: f(a)f(b) < 0
Method:
    Given f(x) = x - x^(1/3) - 2
    Given a range [3,4]
    Repeat:
        Let m = (a+b)/2:
        if ( f(m) < 0 ) a = m
        else b = m
    Stop:
        abs(b-a) < 1e-6 or abs(f(m)) < 1e-6

Properties:
- simple
- safe, robust
- requires only that f be continuous
- slow
- hard to generalizw to systems

*/

// ans = 3.5214

#include <cmath>
#include <iostream>

using namespace std;

double f(double x) {
    return x - pow(x, (1.0 / 3.0)) - 2;
}

int main() {
    double a = 3.0, b = 4.0;

    if (f(a) > f(b)) swap(a, b);
    while (abs(a - b) > 1e-6) {
        double m = (a + b) / 2.0;
        if (f(m) < 0)
            a = m;
        else
            b = m;
    }

    cout << a << endl;

    return 0;
}