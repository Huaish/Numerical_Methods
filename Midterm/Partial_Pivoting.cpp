/*
Gaussian elimination with partial pivoting

Fail:
    - When meeta zero multiple
    - Swamping

Solve:
    Multiples in Gaussian elimination should be kept as small as possible to avoid swamping.
    Partial pivoting: Forces the absolute value of multiples to be no larger than 1

Partial pivoting:
    Searches for the index p of the max pivot in the k-th step
    If p > k then rows p and k are exchanged.
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
#include <string>
#include <vector>

using namespace std;

int main() {
    const int row = 4, col = 4;
    double A[row][col] = {
        {1.19, 2.11, -100, 1},
        {14.2, -0.122, 12.2, -1},
        {0, 100, -99.9, 1},
        {15.3, 0.110, -13.1, -1}};
    double b[row] = {1.12, 3.44, 2.15, 4.16};
    // double A[row][col] = {
    //     {0,0,-1,1},
    //     {1,1,-1,2},
    //     {-1,-1,2,0},
    //     {1,2,0,2}
    // };
    // double b[row] = {1,1,2,0};
    string x[row] = {"x1", "x2", "x3", "x4"};

    // int row = 4, col = 4;
    // cin >> row >> col;
    // double A[row][col];
    // vector<string> x;
    // for ( int i = 0; i < row; i++ ) {
    //     for ( int j = 0; j < col; j++ ) {
    //         cin >> A[i][j];
    //     }
    //     x.push_back("x"+ to_string(i+1));
    // }

    // double b[row];
    // for ( int i = 0; i < row; i++ ) cin >> b[i];

    // Elimination Step
    for (int j = 0; j < col; j++) {
        int p = j;
        for (int k = j + 1; k < row; k++) {
            if (abs(A[k][j]) > abs(A[p][j])) p = k;
        }

        if (p != j) {
            for (int k = 0; k < col; k++) {
                swap(A[p][k], A[j][k]);
            }
            swap(b[p], b[j]);
            swap(x[p], x[j]);
        }

        for (int i = j + 1; i < row; i++) {
            double multiple = A[i][j] / A[j][j];
            for (int k = 0; k < col; k++) {
                A[i][k] -= A[j][k] * multiple;
            }
            b[i] -= b[j] * multiple;
        }
    }

    cout << "------------- Matrix U -------------" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%g\t", A[i][j]);
        }
        cout << endl;
    }

    // (Backward) Substitution step
    for (int j = col - 1; j > 0; j--) {
        for (int i = j - 1; i >= 0; i--) {
            b[i] -= b[j] * (A[i][j] / A[j][j]);
        }
    }
    cout << "------------ Solution X ------------" << endl;
    for (int i = 0; i < row; i++) {
        printf("%s = %g\n", x[i].c_str(), b[i] / A[i][i]);
    }
}