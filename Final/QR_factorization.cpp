/*
QR fractionation of a matrix A
A = [1 2 2; -4 3 2]
1st: Find the first column of Q and R
    y1 = A1 = [1 2 2]
    r11 = ||y1|| = sqrt(1^2 + 2^2 + 2^2) = sqrt(9) = 3
    q1 = y1 / r11 = [1/3 2/3 2/3]
2nd:
    y2 = A2 - q1q1TA2 = [-4 3 2] - [1/3 2/3 2/3] * [1/3 2/3 2/3]T * [-4 3 2] = [-14/3 5/3 2/3]
    r12 = q1TA2 = [1/3 2/3 2/3] * [-4 3 2] = 2
    r22 = ||y2|| = sqrt((-14/3)^2 + (5/3)^2 + (2/3)^2) = sqrt(25/9) = 5/3
    q2 = y2 / r22 = [-14/15 5/15 2/15]
*/

#include <iostream>
#include <cmath>

using namespace std;

double norm(double *v, int n);

int main() {
    const int row = 5;
    const int col = 3;
    double A[row][col] = {
        {3, -1, 2}, 
        {4, 1, 0}, 
        {-3, 2, 1}, 
        {1, 1, 5}, 
        {-2, 0, 3}
    };

    double Q[row][col] = {0};
    double R[col][col] = {0};

    for (int i = 0; i < col; i++) {
        // Calculate yi
        double yi[row] = {0};
        for (int j = 0; j < row; j++) {
            yi[j] = A[j][i];
        }

        for ( int j = 0; j < i; j++ ) {
            // Calculate rji(qjTAi)
            R[j][i] = 0;
            for (int k = 0; k < row; k++) {
                R[j][i] += Q[k][j] * A[k][i];
            }

            // Calculate yi = yi - qj * rji 
            for (int k = 0; k < row; k++) {
                yi[k] -= Q[k][j] * R[j][i];
            }
        }

        // Calculate rii = norm(yi)
        R[i][i] = norm(yi, row);

        // Calculate qi = yi / rii
        for (int j = 0; j < row; j++) {
            Q[j][i] = yi[j] / R[i][i];
        }
    }

    // Print Q
    cout << "------------------- Q -------------------" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << Q[i][j] << " ";
        }
        cout << endl;
    }

    // Print R
    cout << "------------------- R -------------------" << endl;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < col; j++) {
            cout << R[i][j] << " ";
        }
        cout << endl;
    }
}

double norm(double *v, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += v[i] * v[i];
    }
    return sqrt(sum);
}

/*
Q = 
0.480384 -0.26969 0.405732 
0.640513 0.549369 -0.223648 
-0.480384 0.659242 -0.0310072 
0.160128 0.429506 0.691395 
-0.320256 -0.0799082 0.553511 
R = 
6.245 -0.640513 0.320256 
0 2.56705 2.02767 
0 0 5.89797 
*/