/*
Newton's divided difference interpolation
Example:
Find an interpolating polynomial for the data points (0,2), (2,2), (3,4) and (1,0)
0 | 1
  |     (2-1)/(2-0) = 1/2
2 | 2                       (2-1/2)/(3-2) = 1/2
  |     (4-2)/(3-2) = 2                         (0-1/2)/(1-0) = -1/2
3 | 4                       (2-2)/(1-2) = 0
  |     (0-4)/(1-3) = 2
1 | 0
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

double F(int begin, int end) {
    if (begin == end)
        return points[begin].y;
    return (F(begin + 1, end) - F(begin, end - 1)) / (points[end].x - points[begin].x);
}

int main() {
    points.push_back(Point(0.6, 1.433329));
    points.push_back(Point(0.7, 1.632316));
    points.push_back(Point(0.8, 1.896481));
    points.push_back(Point(0.9, 2.247908));
    points.push_back(Point(1.0, 2.718282));
    
    int n = points.size();
    double x = 0.82;
    double ans = 0;
    double x_pow = 1;

    for (int i = 0; i < n; i++) {
        ans += F(0, i) * x_pow;
        x_pow *= (x - points[i].x);
    }

    printf("P(%g) = %g\n", x, ans);

    return 0;

}

/*
P(0.82) = 1.95891
P(0.98) = 2.61285
*/