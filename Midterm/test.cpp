#include <cmath>
#include <iostream>

using namespace std;

double f1(double x1, double x2, double x3) {
    return sin(x1) + x2 * x2 + log(x3) - 7;
}
double f2(double x1, double x2, double x3) {
    return 3 * x1 + 2 * x2 - pow(x3, 3) + 1;
}
double f3(double x1, double x2, double x3) {
    return x1 + x2 + x3 - 5;
}

double df1_dx1(double x1, double x2, double x3) {
    return cos(x1);
}

double df1_dx2(double x1, double x2, double x3) {
    return 2 * x2;
}

double df1_dx3(double x1, double x2, double x3) {
    return 1.0 / x3;
}

double df2_dx1(double x1, double x2, double x3) {
    return 3;
}

double df2_dx2(double x1, double x2, double x3) {
    return 2;
}

double df2_dx3(double x1, double x2, double x3) {
    return -3 * x3 * x3;
}

double df3_dx1(double x1, double x2, double x3) {
    return 1;
}

double df3_dx2(double x1, double x2, double x3) {
    return 1;
}

double df3_dx3(double x1, double x2, double x3) {
    return 1;
}

// function pointer 2D array for f1_h, f1_k, f1_r, f2_h, f2_k, f2_r, f3_h, f3_k, f3_r
double (*d[3][3])(double, double, double) = {
    {df1_dx1, df1_dx2, df1_dx3},
    {df2_dx1, df2_dx2, df2_dx3},
    {df3_dx1, df3_dx2, df3_dx3},
};

// function pointer array for f1, f2, f3
double (*f[3])(double, double, double) = {f1, f2, f3};

int main() {
    const int n = 3;
    double D[n][n];
    double F[n];
    double x1 = 0, x2 = 2, x3 = 2;

    while (true) {
        // solve Df(xk)s = -F(xk)

        // set F and D
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                D[i][j] = d[i][j](x1, x2, x3);
            }
            F[i] = -f[i](x1, x2, x3);
        }

        for (int j = 0; j < n; j++) {
            for (int i = j + 1; i < n; i++) {
                double multiple = D[i][j] / D[j][j];
                for (int x2 = 0; x2 < n; x2++) {
                    D[i][x2] -= D[j][x2] * multiple;
                }

                F[i] -= F[j] * multiple;
            }
        }

        for (int j = n - 1; j > 0; j--) {
            for (int i = j - 1; i >= 0; i--) {
                F[i] -= F[j] * (D[i][j] / D[j][j]);
            }
        }

        bool stop = true;
        for (int i = 0; i < n; i++)
            if (abs(F[i] / D[i][i]) > 1e-6) stop = false;
        if (stop) break;

        x1 += F[0] / D[0][0];
        x2 += F[1] / D[1][1];
        x3 += F[2] / D[2][2];
    }

    printf("%g\n%g\n%g\n", x1, x2, x3);

    return 0;
}