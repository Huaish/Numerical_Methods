#include<iostream>
#include<cmath>

using namespace std;

double f1( double x, double y ) {
    return x + y - 20;
}
double f2( double x, double y ) {
    return x*y + x*sqrt(y) + sqrt(x)*y + sqrt(x)*sqrt(y) - 155.55;
}


double df1_dx(double x, double y) {
    return 1;
}

double df1_dy(double x, double y) {
    return 1;
}

double df2_dx(double x, double y) {
    return y + sqrt(y) + 0.5 * pow(x, -0.5) * y + 0.5 * pow(x, -0.5)*sqrt(y);
}

double df2_dy(double x, double y) {
    return x + 0.5*x*pow(y, -0.5) + sqrt(x) + 0.5*sqrt(x)*pow(y, -0.5);
}



double (*d[2][2])(double, double) = {
    {df1_dx, df1_dy},
    {df2_dx, df2_dy},
};

// function pointer array for f1, f2
double (*f[2])(double, double) = {f1, f2};

int main() {
    const int n = 2;
    double D[n][n];
    double F[n];
    double x = 5, y = 10;

    while ( true ) {

        // solve Df(xk)s = -F(xk)

        // set F and D
        for ( int i = 0; i < n; i++ ) {
            for ( int j = 0; j < n; j++ ) {
                D[i][j] = d[i][j](x, y);
            }
            F[i] = -f[i](x, y);
        }


        for ( int j = 0; j < n; j++ ) {
            for ( int i = j+1; i < n; i++ ) {
                double multiple = D[i][j] / D[j][j];
                for ( int y = 0; y < n; y++ ) {
                    D[i][y] -= D[j][y] * multiple;
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

        x += F[0] / D[0][0];
        y += F[1] / D[1][1];
    }

    printf("%g\n%g\n", x, y);


    return 0;
}