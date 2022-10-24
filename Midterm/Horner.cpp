
// Nested multiplication (Horner's method)
// P(x) = 1 + x + x^2 + ... x^50
// x = 1.0001
// ans = 51.1277

#include<iostream>
#include<cmath>

using namespace std;

int main() {
    double x = 1.0001;
    double x_pow = 1;
    double ans = 0;

    for ( int i = 0; i <= 50; i++ ) {
        ans += x_pow;
        x_pow *= x;
    }

    cout << ans << endl;

    return 0;
}