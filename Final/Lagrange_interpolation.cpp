/*
Lagrange interpolation
P(x) = sum from i=0 to n of f(xi) * L(x, i)
L(x, i) = product from j=0 to j!=i of (x - xj) / (xi - xj)M

Example:
Find an interpolating polynomial for the data points (0,2), (1,1), (2,0) and (3,-1)
P(x) =
    2 * { [(x-1)(x-2)(x-3)] / [(0-1)(0-2)(0-3)] } +
    1 * { [(x-0)(x-2)(x-3)] / [(1-0)(1-2)(1-3)] } +
    0 * { [(x-0)(x-1)(x-3)] / [(2-0)(2-1)(2-3)] } +
    (-1) * { [(x-0)(x-1)(x-2)] / [(3-0)(3-1)(3-2)] }
    }
*/

#include <iostream>

using namespace std;

struct Point {
    double x;
    double y;
};

double L(double x, int i, Point* points, int n)
{
    double result = 1;
    for (int j = 0; j < n; j++) {
        if (j != i) {
            result *= (x - points[j].x) / (points[i].x - points[j].x);
        }
    }
    return result;
}

double P(double x, Point* points, int n)
{
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += points[i].y * L(x, i, points, n);
    }
    return result;
}

int main()
{
    Point points[] = { 
        { 1.00, 0.1924 }, 
        { 1.05, 0.2414 }, 
        { 1.10, 0.2933 }, 
        { 1.15, 0.3492 } };
    int n = sizeof(points) / sizeof(Point);
    double x = 1.09;
    cout << "P(" << x << ") = " << P(x, points, n) << endl;
    return 0;
}

// ans = P(1.09) = 0.282635