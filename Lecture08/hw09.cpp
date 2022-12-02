/*
Newton's divided differences
*/

#include <iostream>
#include <vector>
using namespace std;

struct Point {
    double x;
    double y;
    Point(double x, double y) : x(x), y(y) {}
};

vector<Point> points;

double func(int begin, int end) {
    if (begin == end)
        return points[begin].y;
    return (func(begin + 1, end) - func(begin, end - 1)) / (points[end].x - points[begin].x);
}

int main() {
    int n = 5;
    points.push_back(Point(0.6, 1.433329));
    points.push_back(Point(0.7, 1.632316));
    points.push_back(Point(0.8, 1.896481));
    points.push_back(Point(0.9, 2.247908));
    points.push_back(Point(1.0, 2.718282));

    double x = 0.82;
    double ans = 0;
    double x_pow = 1;

    for (int i = 0; i < n; i++) {
        ans += func(0, i) * x_pow;
        x_pow *= (x - points[i].x);
    }

    printf("P(%g) = %g\n", x, ans);

    x = 0.98;
    ans = 0;
    x_pow = 1;

    for (int i = 0; i < n; i++) {
        ans += func(0, i) * x_pow;
        x_pow *= (x - points[i].x);
    }

    printf("P(%g) = %g\n", x, ans);

    return 0;
}