#include <cmath>
#include <iostream>

using namespace std;

double f1(double x1, double x2, double x3, double x4) {
    return 1.19 * x1 + 2.11 * x2 - 100 * x3 + x4 - 1.12;
}

double f2(double x1, double x2, double x3, double x4) {
    return 14.2 * x1 - 0.122 * x2 + 12.2 * x3 - x4 - 3.44;
}

double f3(double x1, double x2, double x3, double x4) {
    return 100 * x2 - 99.9 * x3 + x4 - 2.15;
}

double f4(double x1, double x2, double x3, double x4) {
    return 15.3 * x1 + 0.11 * x2 - 13.1 * x3 - x4 - 4.16;
}

int main() {
    double x1 = -0.0207, x2 = -1.1826, x3 = 0.01267, x4 = 0.1768;
    cout << f1(x1, x2, x3, x4) << endl;
    cout << f2(x1, x2, x3, x4) << endl;
    cout << f3(x1, x2, x3, x4) << endl;
    cout << f4(x1, x2, x3, x4) << endl;
    return 0;
}