/*
Gauss-Newton algorithm for solving nonlinear least squares problems
minimize ||r(x)||^2
where r(x) is a vector-valued function of x.
The algorithm is based on the following steps:
1. Compute the Jacobian Dr(x) = dr/dx
2. Compute the Gauss-Newton update
3. Update x = x + dx (dx = - (Dr^TDr)^-1 Dr^T r(x))
4. Repeat steps 1-3 until convergence
*/


#include <cmath>
#include <iostream>

using namespace std;

double _x1 = -1, _y1 = 0, _x2 = 1, _y2 = 0.5, _x3 = 1, _y3 = -0.5, _x4 = 0, _y4 = 1;
double r1 = 1, r2 = 0.5, r3 = 0.5, r4 = 0.5;

double f1(double x, double y, double k) { return sqrt(pow(_x1 - x, 2) + pow(_y1 - y, 2)) - (r1 + k); }
double f2(double x, double y, double k) { return sqrt(pow(_x2 - x, 2) + pow(_y2 - y, 2)) - (r2 + k); }
double f3(double x, double y, double k) { return sqrt(pow(_x3 - x, 2) + pow(_y3 - y, 2)) - (r3 + k); }
double f4(double x, double y, double k) { return sqrt(pow(_x4 - x, 2) + pow(_y4 - y, 2)) - (r4 + k); }

double dr1_dx(double x, double y, double k) { return (x - _x1) / (sqrt(pow(x - _x1, 2) + pow(y - _y1, 2))); }

double dr1_dy(double x, double y, double k) { return (y - _y1) / (sqrt(pow(x - _x1, 2) + pow(y - _y1, 2))); }

double dr1_dk(double x, double y, double k) { return -1; }

double dr2_dx(double x, double y, double k) { return (x - _x2) / (sqrt(pow(x - _x2, 2) + pow(y - _y2, 2))); }

double dr2_dy(double x, double y, double k) { return (y - _y2) / (sqrt(pow(x - _x2, 2) + pow(y - _y2, 2))); }

double dr2_dk(double x, double y, double k) { return -1; }

double dr3_dx(double x, double y, double k) { return (x - _x3) / (sqrt(pow(x - _x3, 2) + pow(y - _y3, 2))); }

double dr3_dy(double x, double y, double k) { return (y - _y3) / (sqrt(pow(x - _x3, 2) + pow(y - _y3, 2))); }

double dr3_dk(double x, double y, double k) { return -1; }

double dr4_dx(double x, double y, double k) { return (x - _x4) / (sqrt(pow(x - _x4, 2) + pow(y - _y4, 2))); }

double dr4_dy(double x, double y, double k) { return (y - _y4) / (sqrt(pow(x - _x4, 2) + pow(y - _y4, 2))); }

double dr4_dk(double x, double y, double k) { return -1; }

const int n = 3, m = 4;

// function pointer 2D array for f1_h, f1_k, f1_r, f2_h, f2_k, f2_r, f3_h, f3_k, f3_r
double (*d[m][n])(double, double, double) = { { dr1_dx, dr1_dy, dr1_dk }, { dr2_dx, dr2_dy, dr2_dk },
    { dr3_dx, dr3_dy, dr3_dk }, { dr4_dx, dr4_dy, dr4_dk } };

// function pointer array for f1, f2, f3
double (*f[m])(double, double, double) = { f1, f2, f3, f4 };

double* solve_normal_equations(double A[m][n], double b[n]) {
    double* x = new double[n];
    double AT[n][m];
    double ATA[n][n];
    double ATb[n];

    // set AT
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            AT[i][j] = A[j][i];
        }
    }

    // set ATA
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ATA[i][j] = 0;
            for (int k = 0; k < m; k++) {
                ATA[i][j] += AT[i][k] * A[k][j];
            }
        }
    }

    // set ATb
    for (int i = 0; i < n; i++) {
        ATb[i] = 0;
        for (int j = 0; j < m; j++) {
            ATb[i] += AT[i][j] * b[j];
        }
    }

    // Solve AT_A * x = AT_y (Ax = b) -> Normal equations
    // Elimination step

    // Forward elimination
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double ratio = ATA[j][i] / ATA[i][i];
            for (int k = 0; k < n; k++) {
                ATA[j][k] -= ratio * ATA[i][k];
            }
            ATb[j] -= ratio * ATb[i];
        }
    }

    // Backward substitution
    for (int i = n - 1; i >= 0; i--) {
        x[i] = ATb[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= ATA[i][j] * x[j];
        }
        x[i] /= ATA[i][i];
    }

    return x;
}

int main() {
    double D[m][n], D_T[n][m];
    double r[m];
    // double x = 1.0 / 3, y = 0, k = 1.0 / 3;
    double x[n] = { 1.0 / 3, 0, 1.0 / 3 };

    double A[n][n];
    double b[n];
    double* dx;

    while (true) {
        // set r and Dr
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                D[i][j] = d[i][j](x[0], x[1], x[2]);
            }
            r[i] = -f[i](x[0], x[1], x[2]);
        }

        // Calculate dx
        dx = solve_normal_equations(D, r);

        
        // Check if dx is small enough
        bool stop = true;
        for (int i = 0; i < n; i++)
            if (abs(dx[i]) > 1e-6) stop = false;
        if (stop) break;

        // Update x
        for (int i = 0; i < n; i++) {
            x[i] += dx[i];
        }
    }

    // printf("x: %g\ny: %g\nk: %g\n", x, y, k);
    printf("x: %g\ny: %g\nk: %g\n", x[0], x[1], x[2]);

    return 0;
}

/*
x: 0.311385
y: 0.112268
k: 0.367164
*/