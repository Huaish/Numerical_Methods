#include <cmath>
#include <iostream>

using namespace std;

double _x1 = -1, _y1 = 0, _x2 = 1, _y2 = 0.5, _x3 = 1, _y3 = -0.5, _x4 = 0, _y4 = 1;
double r1 = 1, r2 = 0.5, r3 = 0.5, r4 = 0.5;

double f1(double x, double y, double k) { return sqrt(pow(_x1 - x, 2) + pow(_y1 - y, 2)) - (r1 + k); }
double f2(double x, double y, double k) { return sqrt(pow(_x2 - x, 2) + pow(_y2 - y, 2)) - (r2 + k); }
double f3(double x, double y, double k) { return sqrt(pow(_x3 - x, 2) + pow(_y3 - y, 2)) - (r3 + k); }
double f4(double x, double y, double k) { return sqrt(pow(_x4 - x, 2) + pow(_y4 - y, 2)) - (r4 + k); }

double df1_dh(double x, double y, double k) { return (x - _x1) / (sqrt(pow(x - _x1, 2) + pow(y - _y1, 2))); }

double df1_dk(double x, double y, double k) { return (y - _y1) / (sqrt(pow(x - _x1, 2) + pow(y - _y1, 2))); }

double df1_dr(double x, double y, double k) { return -1; }

double df2_dh(double x, double y, double k) { return (x - _x2) / (sqrt(pow(x - _x2, 2) + pow(y - _y2, 2))); }

double df2_dk(double x, double y, double k) { return (y - _y2) / (sqrt(pow(x - _x2, 2) + pow(y - _y2, 2))); }

double df2_dr(double x, double y, double k) { return -1; }

double df3_dh(double x, double y, double k) { return (x - _x3) / (sqrt(pow(x - _x3, 2) + pow(y - _y3, 2))); }

double df3_dk(double x, double y, double k) { return (y - _y3) / (sqrt(pow(x - _x3, 2) + pow(y - _y3, 2))); }

double df3_dr(double x, double y, double k) { return -1; }

double df4_dh(double x, double y, double k) { return (x - _x4) / (sqrt(pow(x - _x4, 2) + pow(y - _y4, 2))); }

double df4_dk(double x, double y, double k) { return (y - _y4) / (sqrt(pow(x - _x4, 2) + pow(y - _y4, 2))); }

double df4_dr(double x, double y, double k) { return -1; }

// function pointer 2D array for f1_h, f1_k, f1_r, f2_h, f2_k, f2_r, f3_h, f3_k, f3_r
double (*d[4][3])(double, double, double) = { { df1_dh, df1_dk, df1_dr }, { df2_dh, df2_dk, df2_dr },
    { df3_dh, df3_dk, df3_dr }, { df4_dh, df4_dk, df4_dr } };

// function pointer array for f1, f2, f3
double (*f[4])(double, double, double) = { f1, f2, f3, f4 };

int main()
{
    const int n = 3, m = 4;
    double D[m][n], D_T[n][m];
    double r[m];
    double x = 1.0 / 3, y = 0, k = 1.0 / 3;

    double A[n][n];
    double b[n];

    while (true) {
        // solve Df(xk)s = -r(xk)

        // set r and D
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                D[i][j] = d[i][j](x, y, k);
            }
            r[i] = f[i](x, y, k);
        }

        // set D_T
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                D_T[i][j] = D[j][i];
            }
        }

        // set A = D_T * D
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = 0;
                for (int y = 0; y < m; y++) {
                    A[i][j] += D_T[i][y] * D[y][j];
                }
            }
        }

        // set b = D_T * r
        for (int i = 0; i < n; i++) {
            b[i] = 0;
            for (int j = 0; j < m; j++) {
                b[i] -= D_T[i][j] * r[j];
            }
        }

        // solve Ax = b
        for (int j = 0; j < n; j++) {
            for (int i = j + 1; i < n; i++) {
                double multiple = A[i][j] / A[j][j];
                for (int y = 0; y < n; y++) {
                    A[i][y] -= A[j][y] * multiple;
                }

                b[i] -= b[j] * multiple;
            }
        }

        for (int j = n - 1; j > 0; j--) {
            for (int i = j - 1; i >= 0; i--) {
                b[i] -= b[j] * (A[i][j] / A[j][j]);
            }
        }

        bool stop = true;
        for (int i = 0; i < n; i++)
            if (abs(b[i] / A[i][i]) > 1e-6)
                stop = false;
        if (stop)
            break;

        x += b[0] / A[0][0];
        y += b[1] / A[1][1];
        k += b[2] / A[2][2];
    }

    printf("x: %g\ny: %g\nk: %g\n", x, y, k);

    return 0;
}