/*
Gauss-Seidel method
Use the most recently updated values of the knowns, even if the updating occurs in the current step

Ax = b
(L + D + U)x = b
(L + D)xk+1 = b - Uk
Dxk+1 = b - Uxk - Lxk+1
xk+1 = D-1(b - Uxk - Lxk+1)

x0 = initial vector
xk+1 = D-1(b - Uxk - Lxk+1), k = 0,1,2...
*/

/*
Please use Gauss-Seidel method to solve the following system of 10 equations in 10 unknowns:
aii = -4
aij = 2 if |i-j| = 1
aij = 0 if |i-j| >= 2
bT = [2,3,4,5,6,7,8,9,10,11]
*/

#include <cmath>
#include <iostream>

using namespace std;

int main() {
    const int row = 10, col = 10;
    double A[row][col] = {0};
    double L[row][col] = {0}, U[row][col] = {0};
    double b[row] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == j) {
                A[i][j] = -4;
            } else if (abs(i - j) == 1) {
                A[i][j] = 2;
                if (i > j)
                    L[i][j] = 2;
                else
                    U[i][j] = 2;
            }
        }
    }

    double x0[row] = {0}, x1[row] = {0};

    bool stop = false;
    while (!stop) {
        stop = true;
        double tmp[row] = {0};
        for (int i = 0; i < row; i++) x0[i] = x1[i];

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                tmp[i] += U[i][j] * x1[j];
            }

            for (int j = 0; j < col; j++) {
                tmp[i] += L[i][j] * x1[j];
            }

            x1[i] = (b[i] - tmp[i]) / A[i][i];
            if (abs(x1[i] - x0[i]) > 1e-6) stop = false;
        }
    }

    for (int i = 0; i < row; i++) {
        printf("x%d = %g\n", i + 1, x1[i]);
    }

    return 0;
}