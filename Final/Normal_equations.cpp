/*
Normal equations
Example:
x1 + x2 = 2
x1 - x2 = 1
x1 + x2 = 3

A = [1 1; 1 -1; 1 1], b = [2; 1; 3]
A^T * A = [3 1; 1 3]
A^T * b = [6; 4]
Solve A^T * A  * x = A^T * b
       nm * mn * x = n  * 1
       n  * n  * x = n  * 1
       2  * 2  * x = 2  * 1
=> [3 1; 1 3][x1; x2] = [6; 4]
Get x = [7/4; 3/4]
        
*/
#include<iostream>

using namespace std;

int main() {
    // model: f(x) = a + bx + cx2 + dx3
    const int m = 4; // m unknowns
    const int n = 13; // n equations
    double y[n] = {6.3806, 7.1338, 9.1662, 11.5545, 15.6414,
                   22.7371, 32.0696, 47.0756, 73.1596, 111.4684,
                   175.9895, 278.5550, 446.4441};
    double x[n];

    x[0] = 0.0;
    for (int i = 1; i < n; i++) {
        x[i] = x[i - 1] + 0.25;
    }

    double A[n][m];
    for (int i = 0; i < n; i++) {
        A[i][0] = 1.0;
        A[i][1] = x[i];
        A[i][2] = x[i] * x[i];
        A[i][3] = x[i] * x[i] * x[i];
    }

    double AT[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            AT[i][j] = A[j][i];
        }
    }

    double AT_A[m][m];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            AT_A[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                AT_A[i][j] += AT[i][k] * A[k][j];
            }
        }
    }

    double AT_y[m];
    for (int i = 0; i < m; i++) {
        AT_y[i] = 0.0;
        for (int j = 0; j < n; j++) {
            AT_y[i] += AT[i][j] * y[j];
        }
    }

    // Solve AT_A * x = AT_y (Ax = b) -> Normal equations
    // Elimination step
    for (int j = 0; j < m; j++) {
        for (int i = j + 1; i < m; i++) {
            double multiple = AT_A[i][j] / AT_A[j][j];
            for (int k = 0; k < m; k++) {
                AT_A[i][k] -= AT_A[j][k] * multiple;
            }
            AT_y[i] -= AT_y[j] * multiple;
        }
    }

    // Back substitution
    double x_sol[m];
    for (int i = m - 1; i >= 0; i--) {
        x_sol[i] = AT_y[i];
        for (int j = i + 1; j < m; j++) {
            x_sol[i] -= AT_A[i][j] * x_sol[j];
        }
        x_sol[i] /= AT_A[i][i];
    }

    cout << "------------ Solution ------------" << endl;
    cout << "x1 = " << x_sol[0] << endl;
    cout << "x2 = " << x_sol[1] << endl;
    cout << "x3 = " << x_sol[2] << endl;
    cout << "x4 = " << x_sol[3] << endl;
}

/*
x1 = -5.28034
x2 = 103.415
x3 = -128.348
x4 = 47.3747
*/