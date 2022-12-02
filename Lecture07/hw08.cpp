#include <cmath>
#include <iostream>

using namespace std;

double _x1 = 1.00, _y1 = 0.1924;
double _x2 = 1.05, _y2 = 0.2414;
double _x3 = 1.10, _y3 = 0.2933;
double _x4 = 1.15, _y4 = 0.3492;

double f(double x) {
    return _y1 * ((x - _x2) * (x - _x3) * (x - _x4)) / ((_x1 - _x2) * (_x1 - _x3) * (_x1 - _x4)) +
           _y2 * ((x - _x1) * (x - _x3) * (x - _x4)) / ((_x2 - _x1) * (_x2 - _x3) * (_x2 - _x4)) +
           _y3 * ((x - _x1) * (x - _x2) * (x - _x4)) / ((_x3 - _x1) * (_x3 - _x2) * (_x3 - _x4)) +
           _y4 * ((x - _x1) * (x - _x2) * (x - _x3)) / ((_x4 - _x1) * (_x4 - _x2) * (_x4 - _x3));
}

int main() {
    double x = 1.09;
    cout << "f(" << x << ") = " << f(x) << endl;
    return 0;
}