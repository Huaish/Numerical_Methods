/*
Jacobi method
A form of fixed-point iteration

Convergence is guaranteed if the matrix A is diagonally dominant
Strictly diagonally dominant: |a_ii| >= sum_{j != i} |a_ij|

Method
Ax = b
(D + L + U)x0 = b
Dx = b - (L + U)x0
x0 = D^-1(b - (L + U)x0)
-----------------------------------------------------------------
x0 = initial vector
xk+1 = D^-1(b - (L + U)xk), k = 0,1,2,...
-----------------------------------------------------------------
Example:
3u + v = 5
u + 2v = 5
D = [3 0]   L = [0 0]   U = [0 1]   b = [5]
    [0 2]       [1 0]       [0 0]       [5]

           D-1    b    (L+U) xk
[uk+1] = [1/3 0]([5] - [1 1][uk])
[vk+1]   [0 1/2]([5] - [1 0][vk])
*/
/*
Please use Jacobi to solve the following system of 10 equations in 10 unknowns:
aii = -4
aij = 2 if |i-j| = 1
aij = 0 if |i-j| >= 2
bT = [2,3,4,5,6,7,8,9,10,11]
*/

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int row = 10, col = 10;
    double A[row][col] = {0};
    double L_plus_U[row][col] = {0};

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == j)
                A[i][j] = -4;
            else if (abs(i - j) == 1) {
                A[i][j] = 2;
                L_plus_U[i][j] = 2;
            } else {
                A[i][j] = 0;
                L_plus_U[i][j] = 0;
            }
        }
    }

    double b[row] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    double x0[row] = {0};
    double x1[row] = {0};

    while (true) {
        // (L+U)x0
        double tmp[row] = {0};
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                tmp[i] += L_plus_U[i][j] * x0[j];
            }
        }

        // b - (L+U)x0
        for (int i = 0; i < row; i++) {
            tmp[i] = b[i] - tmp[i];
        }

        // D^-1(b - (L+U)x0)
        for (int i = 0; i < row; i++) {
            x1[i] = tmp[i] / A[i][i];
        }

        bool stop = true;
        for (int i = 0; i < row; i++) {
            if (abs(x1[i] - x0[i]) > 1e-6) {
                stop = false;
                break;
            }
        }

        if (stop)
            break;

        for (int i = 0; i < row; i++) {
            x0[i] = x1[i];
        }
    }

    for (int i = 0; i < row; i++) {
        cout << "x" << i + 1 << " = " << x1[i] << endl;
    }

    return 0;
}