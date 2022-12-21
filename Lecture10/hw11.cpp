#include <cmath>
#include <iostream>

using namespace std;

double normalize(double* A, double* Q, int n);
double dot(double* A, double* B, int n);
int main()
{
    const int row = 5;
    const int col = 3;
    double A[row][col] = { { 3, -1, 2 }, { 4, 1, 0 }, { -3, 2, 1 }, { 1, 1, 5 }, { -2, 0, 3 } };
    double Q[row][col] = { 0 };
    double R[col][col] = { 0 };

    double* tmp = new double[row];
    double* tmp2 = new double[row];
    double* y = new double[row];
    for (int i = 0; i < row; i++) {
        tmp[i] = A[i][0];
    }

    R[0][0] = normalize(tmp, tmp2, row);
    for (int i = 0; i < row; i++) {
        Q[i][0] = tmp2[i];
    }

    for (int i = 1; i < col; i++) {
        for (int j = 0; j < row; j++) {
            y[j] = A[j][i];
        }
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < row; k++) {
                tmp[k] = Q[k][j];
            }
            R[j][i] = dot(tmp, y, row);
            for (int k = 0; k < row; k++) {
                y[k] -= R[j][i] * Q[k][j];
            }

            R[i][i] = normalize(y, tmp2, row);

            for (int k = 0; k < row; k++) {
                Q[k][i] = tmp2[k];
            }
        }
    }

    cout << "------------------- Q -------------------" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%f\t", Q[i][j]);
        }
        cout << endl;
    }

    cout << "------------------- R -------------------" << endl;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < col; j++) {
            printf("%f\t", R[i][j]);
        }
        cout << endl;
    }
    return 0;
}

double normalize(double* A, double* Q, int n)
{
    double norm = 0.0;
    for (int i = 0; i < n; i++) {
        norm += A[i] * A[i];
    }
    norm = sqrt(norm);
    for (int i = 0; i < n; i++) {
        Q[i] = A[i] / norm;
    }

    return norm;
}

double dot(double* A, double* B, int n)
{
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += A[i] * B[i];
    }
    return result;
}