/*
Fixed point iteration
Def: The real number x is a fixed point of a function g if g(x) = x
Approach:
    1. Given a function f(x), select a function g(x) such that f(x) = 0 -> g(x) = x
    2. x0 = initial guess
       xi+1 = g(xi), i = 0,1,2...
    3. Stop until abs(xi+1-xi) < 1e-6

Linear Convergence: S = |g'(r)| < 1

Bisection vs FPI
if S > 0.5, then Bisection faster
else FPI faster
*/

// x^3 = 2x + 2
// ans = 1.76929

#include <cmath>
#include <iostream>

using namespace std;

double g(double x) {
    return pow(2 * x + 2, 1.0 / 3.0);
}

int main() {
    double x0 = 1, x1 = 1;
    do {
        swap(x0, x1);
        x1 = g(x0);
    } while (abs(x1 - x0) > 1e-6);

    cout << x1 << endl;
    return 0;
}