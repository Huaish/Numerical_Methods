/*
Jacobian matrix
3 variables: x = (u,v,w)
3 functions: f1, f2, f3
Df(x) = [df1/du df1/dv df1/dw]
        [df2/du df2/dv df2/dw]
        [df3/du df3/dv df3/dw]

Multivariate Newton's method Algorithm
    x0 = initial vector
    xk+1 = xk - (Df(xk))-1 * F(xk), k = 0,1,2,3...
    ----------------------------------------------
    Let s = -(Df(xk))-1 * F(xk)
    Df(xk)s = -F(xk) -> Solving Ax = b, s is the solution of Df(xk)s = -F(xk)
    ----------------------------------------------
    x0 = initial vector
    solve Df(xk)s = -F(xk)
    xk+1 = xk + s, k = 0,1,2,...
*/
/*
Example:
    f1 = v - u^3 = 0
    f2 = u^2 + v^2 - 1 = 0
    -----------------------------------------------
    df1/du = -3u^2
    df1/dv = 1              Df(u,v) = [-3u^2 1]
    df2/du = du                       [2u   2v]
    df2/dv = 2v
    -----------------------------------------------
    x0 = (1,2)
    Solve:
        [-3 1][s1] = [-1]
        [2  4][s2] = [-4]
    Get s = (0, -1)
    Update x
        x1 = x0 + s = (1,2) + (0, -1) = (1,1)
    -----------------------------------------------
    x1 = (1,1)
    Solve:
        [-3 1][s1] = [ 0]
        [2  2][s2] = [-1]
    Get s = (-1/8, -3/8)
    Update x
        x2 = x1 + s = (1,1) + (-1/8, -3/8) = (7/8, 5/8)
*/

/*
圓方程式: (x-h)^2 + (y-k)^2 = r^2, 求圓心(h,k)及半徑r
  test1           test2
(-8, -4)        (-1,  6)
( 6,  9)        (-2, -6)
( 4, -9)        ( 5,  0)
*/

#include<iostream>
#include<cmath>

using namespace std;

int _x1 = -8, _y1 = -4, _x2 = 6, _y2 = 9, _x3 = 4, _y3 = -9;

double f1( double h, double k, double r ) {
    return pow(_x1 - h, 2) + pow(_y1 - k, 2) - r*r;
}
double f2( double h, double k, double r ) {
    return pow(_x2 - h, 2) + pow(_y2 - k, 2) - r*r;
}
double f3( double h, double k, double r ) {
    return pow(_x3 - h, 2) + pow(_y3 - k, 2) - r*r;
}

double df1_dh(double h, double k, double r) {
    return -2*(_x1-h);
}

double df1_dk(double h, double k, double r) {
    return -2*(_y1-k);
}

double df1_dr(double h, double k, double r) {
    return -2*r;
}

double df2_dh(double h, double k, double r) {
    return -2*(_x2-h);
}

double df2_dk(double h, double k, double r) {
    return -2*(_y2-k);
}

double df2_dr(double h, double k, double r) {
    return -2*r;
}

double df3_dh(double h, double k, double r) {
    return -2*(_x3-h);
}

double df3_dk(double h, double k, double r) {
    return -2*(_y3-k);
}

double df3_dr(double h, double k, double r) {
    return -2*r;
}

// function pointer 2D array for f1_h, f1_k, f1_r, f2_h, f2_k, f2_r, f3_h, f3_k, f3_r
double (*d[3][3])(double, double, double) = {
    {df1_dh, df1_dk, df1_dr},
    {df2_dh, df2_dk, df2_dr},
    {df3_dh, df3_dk, df3_dr},
};

// function pointer array for f1, f2, f3
double (*f[3])(double, double, double) = {f1, f2, f3};

int main() {
    const int n = 3;
    double D[n][n];
    double F[n];
    double h = 1, k = 1, r = 3;

    cin >> _x1 >> _y1 >> _x2 >> _y2 >> _x3 >> _y3;

    while ( true ) {

        // solve Df(xk)s = -F(xk)

        // set F and D
        for ( int i = 0; i < n; i++ ) {
            for ( int j = 0; j < n; j++ ) {
                D[i][j] = d[i][j](h, k, r);
            }
            F[i] = -f[i](h, k, r);
        }


        for ( int j = 0; j < n; j++ ) {
            for ( int i = j+1; i < n; i++ ) {
                double multiple = D[i][j] / D[j][j];
                for ( int k = 0; k < n; k++ ) {
                    D[i][k] -= D[j][k] * multiple;
                }

                F[i] -= F[j] * multiple;
            }
        }

        for ( int j = n-1; j > 0; j-- ) {
            for ( int i = j-1; i >= 0; i-- ) {
                F[i] -= F[j] * (D[i][j]/D[j][j]);
            }
        }

        
        bool stop = true;
        for ( int i = 0; i < n; i++ )
            if ( abs(F[i]/D[i][i]) > 1e-6 ) stop = false;
        if ( stop ) break;

        h += F[0] / D[0][0];
        k += F[1] / D[1][1];
        r += F[2] / D[2][2];
    }

    printf("%g\n%g\n%g\n", h, k, r);


    return 0;
}