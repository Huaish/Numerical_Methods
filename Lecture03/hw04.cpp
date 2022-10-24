#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
LU Factorization
Input: A square matrix A
Output: L and U, the lower and upper triangular matrices
such that A = LU

For example,

2x + y = 1
y + 2z = 1
2x + 4y + 5z + w = 2
8x + 5y + 3w = 0

A = [ 2  1  0  0  1 ] = [ 2  1  0  0  1 ]
    [ 0  1  2  0  1 ] = [ 0  1  2  0  1 ]
    [ 2  4  5  1  2 ] = [ 0  0 -1  1 -2 ]
    [ 8  5  0  3  0 ] = [ 0  0  0  1 -1 ]

L = [ 1  0  0  0 ]
    [ 0  1  0  0 ]
    [ 1  3  1  0 ]
    [ 4  1  2  1 ]

U = [ 2  1  0  0 ]
    [ 0  1  2  0 ]
    [ 0  0 -1  0 ]
    [ 0  0  0  1 ]

*/

int main() {
    int m = 0, n = 0;
    cin >> m >> n;
    vector< vector<double> > A(m, vector<double>(n));
    vector< vector<double> > L(m, vector<double>(n));
    vector<double> ans(m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
            if (i == j)
                L[i][j] = 1;
            else
                L[i][j] = 0;
        }
    }


    for (int i = 1; i < m; i++) {
        for (int j = 0; j < i; j++) {
            L[i][j] = A[i][j] / A[j][j];
            for (int k = 0; k < n; k++) {
                A[i][k] = A[i][k] - A[j][k] * L[i][j];
            }
        }
    }

    // print L
    cout << "L: " << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++)

            cout << L[i][j] << " ";

        cout << endl;
    }

    cout << "-----------" << endl;

    // print U
    cout << "U: " << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }

    cout << "-----------" << endl;

    // int x = 0, y = 0, z = 0, w = 0;
    // w = A[3][4] / A[3][3];
    // z = (A[2][4] - A[2][3] * w) / A[2][2];
    // y = (A[1][4] - A[1][3] * w - A[1][2] * z) / A[1][1];
    // x = (A[0][4] - A[0][3] * w - A[0][2] * z - A[0][1] * y) / A[0][0];


    // cout << "x: " << x << endl;
    // cout << "y: " << y << endl;
    // cout << "z: " << z << endl;
    // cout << "w: " << w << endl;


    for ( int i = m - 1; i >= 0; i-- ) {
        double tmp = A[i][m];
        for ( int j = m - 1; j > i; j-- ) {
            tmp -= A[i][j] * ans[j];
        }
        ans[i] = tmp / A[i][i];
    }

    for ( int i = 0; i < m; i++ )
        cout << ans[i] << " ";

    return 0;
}