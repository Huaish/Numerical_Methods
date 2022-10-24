
// f(x) = x - x^(1/3) -2 = 0
// range: [3, 4]
// find |a-b| <= 10 ^ (-6)
// 小數第四位

#include<iostream>
#include<cmath>

using namespace std;

double func( double x ) {
    return x - pow(x, (1.0/3.0)) - 2;
}

int main() {

    double a = 3.0;
    double b = 4.0;
    double c = 0.0;

    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;

    while (abs(a - b) >= 1e-6) {
        c = (a + b) / 2.0;
        double fc = func(c);

        if ( fc > 0 ) {
            b = c;
        }
        else {
            a = c;
        }

    }

    printf("Ans: %.4f\n", c);

    return 0;

}


