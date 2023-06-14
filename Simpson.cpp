#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double function(double x)
{
    return sin(x);
}

double Simpson(long double a, long double b, long double epsilon, int n)
{
    long double h = (b - a)/n;

    long double S0 = function(a) + function(b);
    long double S1 = 0, S2 = 0;

    for(int i = 1; i < n; i++)
    {
        if(i % 2 == 1)
            S1 += function(a + h*i);
        if(i % 2 == 0)
            S2 += function(a + h*i);
    }
    long double I1 = (h/3.)*(S0 + 4.*S1 + 2.*S2);
    cout << "n = " << n << " I = " << I1 << endl;
    n *= 2;
    h = (b - a)/n;
    S2 += S1;

    S1 = 0;
    for(int i = 1; i < n; i+=2)
        S1 += function(a + h*i);

    long double I2 = (h/3)*(S0 + 4*S1 + 2*S2);
    setprecision(20);
    cout << "n = " << n << " I = " << I2 << endl;
    while(abs(I2 - I1) > epsilon)
    {

        I1 = I2;
        n *= 2;
        //cout << "n = " << n << endl;
        h = (b - a)/n;
        S2 += S1;

        S1 = 0;
        for(int i = 1; i < n; i+=2)
            S1 += function(a + h*i);

        I2 = (h/3)*(S0 + 4*S1 + 2*S2);
        //std::fixed;
        setprecision(20);
        cout << "n = " << n << " I = " << I2 << endl;
    }
    return I2;
}

int main() {
    //system("chcp 65001");
    cout << fixed;
    double epsilon;
    int n;
    cout << "Введите epsilon" << endl;
    cin >> epsilon;
    cout << "Введите n" << endl;
    cin >> n;
    epsilon *= 15./16.;
    double result = Simpson(0, M_PI, epsilon, n);
    cout << "Интеграл равен " << result << endl;
    return 0;
}