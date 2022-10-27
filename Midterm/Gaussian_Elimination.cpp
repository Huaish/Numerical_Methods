/*
Gaussian elimination

Approach:
    1. Multiply an equation by a nonzero constant
    2. Add or subtract a multiple of one equation from another

Elimination Step: O(n^3)
    for j = 0 : n
        for i = j+1 : n
            eliminate entry a(i,j) -> 2n + 1 operations
        end
    end

(Backward) Substitution step: O(n^2)
    x1 = (b1 - a12x2 - ... - a1nxn) / a11
    x2 = (b2 - a23x3 - ... - a2nxn) / a22
    ...
    xn = bn / ann
*/

/*
Please use Gaussian elimination to solve
2x + y = 1
y + 2z = 1
2x + 4y + 5z + w = 2
8x + 5y + 3w = 0
*/

#include <cmath>
#include <iostream>

using namespace std;

int main() {
    // const int row = 4, col = 4;
    // double A[row][col] = {
    //     {2,1,0,0},
    //     {0,1,2,0},
    //     {2,4,5,1},
    //     {8,5,0,3}
    // };

    // double b[row] = {1,1,2,0};

    int row = 4, col = 4;
    cin >> row >> col;
    double A[row][col];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            cin >> A[i][j];
    double b[row];
    for (int i = 0; i < row; i++) cin >> b[i];

    // Elimination Step
    for (int j = 0; j < col; j++) {
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
        printf("| %g\n", b[i]);
    }

    // (Backward) Substitution step
    for (int j = col - 1; j > 0; j--) {
        for (int i = j - 1; i >= 0; i--) {
            b[i] -= b[j] * (A[i][j] / A[j][j]);
        }
    }
    cout << "------------ Solution X ------------" << endl;
    for (int i = 0; i < row; i++) {
        printf("x%i=%g\n", i, b[i] / A[i][i]);
    }
}