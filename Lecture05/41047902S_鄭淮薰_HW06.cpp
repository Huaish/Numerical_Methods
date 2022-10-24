#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double MIN = 1e-10;

// Matrix class
class Matrix {
public:
    vector< vector<double> > matrix;

    // Constructor
    Matrix(int rows, int cols) {
        matrix.resize(rows);
        for (int i = 0; i < rows; i++) {
            matrix[i].resize(cols);
        }
    }

    Matrix( double** a, int m, int n ) {
        matrix.resize(m);
        for (int i = 0; i < m; i++) {
            matrix[i].resize(n);
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = a[i][j];
            }
        }
    }

    // Overload operator +
    Matrix operator+(const Matrix& m) {
        Matrix result(m.matrix.size(), m.matrix[0].size());
        for (int i = 0; i < m.matrix.size(); i++) {
            for (int j = 0; j < m.matrix[0].size(); j++) {
                result.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
            }
        }
        return result;
    }

    // Overload operator -
    Matrix operator-(const Matrix& m) {
        Matrix result(m.matrix.size(), m.matrix[0].size());
        for (int i = 0; i < m.matrix.size(); i++) {
            for (int j = 0; j < m.matrix[0].size(); j++) {
                result.matrix[i][j] = matrix[i][j] - m.matrix[i][j];
            }
        }
        return result;
    }

    // Overload operator *
    Matrix operator*(const Matrix& m) {
        Matrix result(matrix.size(), m.matrix[0].size());
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < m.matrix[0].size(); j++) {
                for (int k = 0; k < m.matrix.size(); k++) {
                    result.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
                }
            }
        }
        return result;
    }

    // Overload operator []
    vector<double>& operator[](int i) {
        return matrix[i];
    }

    // Overload operator ==
    bool operator==(const Matrix& m) {
        if (matrix.size() != m.matrix.size() || matrix[0].size() != m.matrix[0].size()) {
            return false;
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (abs(matrix[i][j] - m.matrix[i][j]) > MIN) {
                    return false;
                }
            }
        }
        return true;
    }

    // Overload operator !=
    bool operator!=(const Matrix& m) {
        if (matrix.size() != m.matrix.size() || matrix[0].size() != m.matrix[0].size()) {
            return true;
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (abs(matrix[i][j] - m.matrix[i][j]) > MIN) {
                    return true;
                }
            }
        }
        return false;
    }

    // Matrix inverse
    Matrix inverse() {
        Matrix result(matrix.size(), matrix[0].size());
        for ( int i = 0; i < matrix.size(); i++ ) {
            for ( int j = 0; j < matrix[0].size(); j++ ) {
                if (i == j) {
                    result.matrix[i][j] = 1 / matrix[i][j];
                }
                else {
                    result.matrix[i][j] = 0;
                }

            }
        }

        return result;
    }


    // print matrix
    void print() {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // ~Matrix()
    ~Matrix() {
        matrix.clear();
    }
};

double** createMatrix(int m, int n) {
    double** a = new double*[m];
    for (int i = 0; i < m; i++) {
        a[i] = new double[n];
    }
    return a;
}

int main() {
    // aii = -4
    // aij = 2 if |i-j| = 1
    // aij = 0 if |i-j| >= 2
    // where i,j = 0,2,...,n
    // bT = [2,3,4,5,6,7,8,9,10,11]

    // initialize
    int n = 10;
    double** _A = createMatrix(n, n);
    double** _L = createMatrix(n, n);
    double** _U = createMatrix(n, n);
    double** _D = createMatrix(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                _A[i][j] = -4;
                _D[i][j] = -4;
            } else if (abs(i - j) == 1) {
                _A[i][j] = 2;
                _L[i][j] = 2;
            } else {
                _A[i][j] = 0;
                _U[i][j] = 0;
            }
        }
    }

    Matrix A(_A, n, n);
    Matrix L(_L, n, n);
    Matrix U(_U, n, n);
    Matrix D(_D, n, n);

    // Jacobi Method
    // x0 = (0,0,...,0)
    // xk+1 = D^(-1) * (b - (L+U)*xk)
    // k = 1,2,...,10

    Matrix x0(n, 1); // double x0[1][10] = {0};
    Matrix x1(n, 1); // double x1[1][10] = {0};
    Matrix b(n, 1); // double b[1][10] = {2,3,4,5,6,7,8,9,10,11};
    for (int i = 0; i < n; i++) b[i][0] = i + 2;

    do {
        swap(x0, x1);
        x1 = D.inverse() * (b - ((L+U) * x0));
    } while ( x1 != x0 );

    // print Answer
    x1.print();

    return 0;
}

// Original code
/*

Matrix L_plus_U = L + U;
Matrix D_inverse = D.inverse();
while ( true ) {
    int cnt = 0;
    double sum[11] = {0};
    double sum2[11] = {0};

    // L_plus_U * x0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum[i] += (L_plus_U[i][j]) * x0[j][0];
        }
    }

    // b - L_plus_U * x0
    for (int i = 0; i < n; i++) {
        sum[i] = (b[i][0] - sum[i]);
    }

    // D_inverse * (b - L_plus_U * x0)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum2[i] += sum[i] * D_inverse[i][j];
        }
    }

    // compare x0 and x1
    for (int i = 0; i < n; i++) {
        x1[i][0] = sum2[i];
        if (abs(x1[i][0] - x0[i][0]) < 0.000000001) {
            cnt++;
        }
    }

    if (cnt == 10 ) {
        break;
    }

    // swap x1 and x0
    for ( int i = 0; i < n; i++ ) {
        swap(x1[i][0], x0[i][0]);
    }
}
*/