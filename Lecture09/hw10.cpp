#include <iostream>

using namespace std;

//  f(x) = a + bx + cx2 +dx3

int main() {
    const int n = 13;
    const int m = 4;
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

    // AT*Ac = AT*y
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

    // Elimination Step
    for (int j = 0; j < m; j++) {
        for (int i = j + 1; i < m; i++) {
            double multiple = AT_A[i][j] / AT_A[j][j];
            for (int k = 0; k < m; k++) {
                AT_A[i][k] -= AT_A[j][k] * multiple;
            }
            AT_y[i] -= AT_y[j] * multiple;
        }
    }

    // (Backward) Substitution step
    for (int j = m - 1; j > 0; j--) {
        for (int i = j - 1; i >= 0; i--) {
            AT_y[i] -= AT_y[j] * (AT_A[i][j] / AT_A[j][j]);
        }
    }
    cout << "------------ Solution ------------" << endl;
    string var[] = {"a", "b", "c", "d"};
    for (int i = 0; i < m; i++) {
        printf("%s = %g\n", var[i].c_str(), AT_y[i] / AT_A[i][i]);
    }

    return 0;
}