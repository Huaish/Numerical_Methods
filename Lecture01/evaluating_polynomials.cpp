#include<iostream>

using namespace std;

// p = 1 + x + x^2 + x^3 + ... + x^50
// p(1.0001)

double evaluPoly(  ) {

}

int main() {
    double p = 1;
    double x;
    cout << "Enter x: ";
    cin >> x;
    double x_pow = 1;

    for (int i = 1; i <= 50; i++) {
        x_pow *= x;
        p += x_pow;
    }
    cout << p << endl;

    return 0;
}