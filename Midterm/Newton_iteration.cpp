/*
Newton's iteration
> A refined version of FPI where S is designed to be zero
Given a scalar differentiable function f(x)
1. Start from an initial guess x0
2. for i = 0,1,2..., compute xi+1 = xi - f(xi)/f'(xi)
-----------------------------------------------------
推導：
    f'(x0) = f(x0)/(x0-x1)
    => x1 = x0 - f(x0)/f'(x0)
    => xi+1 = xi - f(xi)/f'(xi)
    => g(x) = x - f(x)/f'(x)
-----------------------------------------------------
Example:
    f(x) = x^3 + x - 1 = 0
    f'(x) = 3x^2 + 1
    => g(x) = x - (x^3 + x - 1) / (3x^2 + 1)
-----------------------------------------------------
Convergence: quadratically convergent
*/

// Each equation has one root. Please use Newton method to find the root of flowing equations
//  x^5 + x = 1 => x^5 + x - 1 = 0, ans = 0.754878
//  lnx + x^2 = 3 => lnx + x^2 - 3 = 0, ans = 1.59214
//  sinx = 6x + 5 => sinx - 6x + 5 = 0, ans = -0.970899

#include <cmath>
#include <iostream>

using namespace std;

double f(double x) {
    // return pow(x, 5) + x - 1;
    // return log(x) + x*x - 3;
    return sin(x) - 6 * x + 5;
}

double df(double x) {
    // return 5 * pow(x, 4) + 1;
    // return 1.0/x + 2*x;
    return cos(x) - 6;
}

int main() {
    double x0 = 1, x1 = 1;

    do {
        swap(x0, x1);
        x1 = x0 - f(x0) / df(x0);
    } while (abs(x1 - x0) > 1e-6);

    cout << x1 << endl;
    return 0;
}

/*
0.754878
1.59214
-0.970899
*/