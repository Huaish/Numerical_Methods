#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const double MIN = 1e-10;


double _x1 = -8;
double _y1 = -4;
double _x2 = 6;
double _y2 = 9;
double _x3 = 4;
double _y3 = -9;

double f1(double h, double k, double r)
{
    return pow(_x1 - h, 2) + pow(_y1 - k, 2) - pow(r, 2);
}

double f2(double h, double k, double r)
{
    return pow(_x2 - h, 2) + pow(_y2 - k, 2) - pow(r, 2);
}

double f3(double h, double k, double r)
{
    return pow(_x3 - h, 2) + pow(_y3 - k, 2) - pow(r, 2);
}

double f1_h(double h, double k, double r)
{
    return -2 * (_x1 - h);
}

double f1_k(double h, double k, double r)
{
    return -2 * (_y1 - k);
}

double f1_r(double h, double k, double r)
{
    return -2 * r;
}

double f2_h(double h, double k, double r)
{
    return -2 * (_x2 - h);
}

double f2_k(double h, double k, double r)
{
    return -2 * (_y2 - k);
}

double f2_r(double h, double k, double r)
{
    return -2 * r;
}

double f3_h(double h, double k, double r)
{
    return -2 * (_x3 - h);
}

double f3_k(double h, double k, double r)
{
    return -2 * (_y3 - k);
}

double f3_r(double h, double k, double r)
{
    return -2 * r;
}

// function pointer 2D array for f1_h, f1_k, f1_r, f2_h, f2_k, f2_r, f3_h, f3_k, f3_r
double (*d[3][3])(double, double, double) = {
    {f1_h, f1_k, f1_r},
    {f2_h, f2_k, f2_r},
    {f3_h, f3_k, f3_r}};

// function pointer array for f1, f2, f3
double (*f[3])(double, double, double) = {f1, f2, f3};

int main()
{
    // Jacobian matrix
    // (x-h)^2 + (y-k)^2 = r^2
    // test1
    // (-8, -4), (6, 9), (4,-9)

    // f1 = (-8-h)^2 + (-4-k)^2 - r^2
    // f2 = (6-h)^2 + (9-k)^2 - r^2
    // f3 = (4-h)^2 + (-9-k)^2 - r^2

    const int n = 3;
    double h = 1;
    double k = 2;
    double r = 3;

    cin >> _x1 >> _y1 >> _x2 >> _y2 >> _x3 >> _y3;

    double D[n][n];
    double F[n] = {0};


    while ( true ) {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                D[i][j] = d[i][j](h, k, r);
            }
        }

        for (int i = 0; i < n; i++)
        {
            F[i] = -f[i](h, k, r);
        }


        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                double tmp = D[j][i] / D[i][i];
                for (int k = 0; k < n; k++) {
                    D[j][k] = D[j][k] - D[i][k] * tmp;
                }
                F[j] = F[j] - F[i] * tmp;
            }
        }


        for (int i = n-1; i >= 0; i--) {
            for ( int j  = i-1; j >= 0; j-- ) {
                double tmp = D[j][i] / D[i][i];
                for (int k = 0; k < n; k++) {
                    D[j][k] = D[j][k] - D[i][k] * tmp;
                }
                F[j] = F[j] - F[i] * tmp;
            }
        }

        double h1 = h + F[0] / D[0][0];
        double k1 = k + F[1] / D[1][1];
        double r1 = r + F[2] / D[2][2];

        if ( abs(F[0]/D[0][0]) < 0.0001 && abs(F[1]/D[1][1]) < 0.0001 && abs(F[2]/D[2][2]) < 0.0001 ) {
            cout << h1 << ", " << k1 << ", " << r1 << endl;
            break;
        }

        h = h1;
        k = k1;
        r = r1;
    }


    return 0;
}
