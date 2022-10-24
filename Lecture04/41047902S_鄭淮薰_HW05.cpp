#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

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

    // PA = LU

    vector< vector<double> > P(m, vector<double>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                P[i][j] = 1;
            else
                P[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        double max = A[i][i];
        int max_index = i;
        for ( int k = i; k < n; k++)
        {
            if (abs(A[k][i]) > abs(max))
            {
                max = A[k][i];
                max_index = k;
            }
        }


        for (int k = 0; k < n; k++)
        {
            double temp = A[i][k];
            A[i][k] = A[max_index][k];
            A[max_index][k] = temp;
            temp = P[i][k];
            P[i][k] = P[max_index][k];
            P[max_index][k] = temp;
        }


        for (int j = 0; j < i; j++)
        {
            L[i][j] = A[i][j] / A[j][j];
            for (int k = 0; k < n; k++) {
                A[i][k] = A[i][k] - A[j][k] * L[i][j];
            }
        }
    }

    // print P
    cout << "P = " << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
        {
            cout << P[i][j] << " ";
        }
        cout << endl;
    }

    cout << "-----------" << endl;

    // print L
    cout << "L: " << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)

            cout << L[i][j] << " ";

        cout << endl;
    }

    cout << "-----------" << endl;

    // print U
    cout << "U: " << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }

    return 0;
}