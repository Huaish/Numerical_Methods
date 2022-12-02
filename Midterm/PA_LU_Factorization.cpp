/*
PA = LU Factorization
Permutation matrix
> A permutation matrix is a n x n matrix consisting of all zeros, except for a single 1 in every row and column.
*/

/*
A =
0   0   -1  1
1   1   -1  2
-1  -1  2   0
1   2   0   2
*/

#include <cmath>
#include <iostream>
using namespace std;

int main() {
    const int row = 4, col = 4;
    double A[row][col] = {
        {1.19, 2.11, -100, 1},
        {14.2, -0.122, 12.2, -1},
        {0, 100, -99.9, 1},
        {15.3, 0.110, -13.1, -1}};

    // int row = 4, col = 4;
    // cin >> row;
    // cin >> col;

    // double A[row][col];
    // for ( int i = 0; i < row; i++ ) {
    //     for ( int j = 0; j < col; j++ ) {
    //         cin >> A[i][j];
    //     }
    // }

    double P[row][col];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == j)
                P[i][i] = 1;
            else
                P[i][j] = 0;
        }
    }

    for (int j = 0; j < col; j++) {
        int p = j;
        for (int k = j + 1; k < row; k++) {
            if (abs(A[k][j]) > abs(A[p][j])) p = k;
        }

        if (p != j) {
            for (int k = 0; k < col; k++) {
                swap(A[p][k], A[j][k]);
                swap(P[p][k], P[j][k]);
            }
        }

        for (int i = j + 1; i < row; i++) {
            double multiple = A[i][j] / A[j][j];
            A[i][j] = multiple;
            for (int k = j + 1; k < col; k++) {
                A[i][k] -= A[j][k] * multiple;
            }
        }
    }

    cout << "-------- Matrix P --------" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%g\t", P[i][j]);
        }
        cout << endl;
    }

    cout << "-------- Matrix L --------" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == j)
                printf("1\t");
            else if (i > j)
                printf("%g\t", A[i][j]);
            else
                printf("0\t");
        }
        cout << endl;
    }

    cout << "-------- Matrix U --------" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i > j)
                printf("0\t");
            else
                printf("%g\t", A[i][j]);
        }
        cout << endl;
    }

    return 0;
}