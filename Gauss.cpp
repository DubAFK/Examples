#include <iostream>
#include <math.h>

using namespace std;

int MaxInColumn(long double **A, int j, int n)
{
    int MaxIndex;
    for (int i = j; i < n; i++) {
        if (i == j)
            MaxIndex = i;
        else {
            if ((abs(A[MaxIndex][j])) < (abs(A[i][j])))
                MaxIndex = i;
        }
    }
    return MaxIndex;
}

int main()
{
    //setlocale(LC_ALL,"rus");
    system("chcp 65001");
    int n;
    double zero = 0.0000000000001;
    bool cont = true;
    cout << "Введите размерность матрицы(N x N): " << endl;
    cin >> n;
    auto **A = new long double*[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = new long double[n];
        for(int j = 0; j < n; j++)
        {
            cout << "A [" << i << ";" << j << "]= ";
            cin >> A[i][j];
        }
    }
    auto *F = new long double[n];
    for(int i = 0; i < n; i++)
    {
        cout << "Введите F[" << i << "]: " << endl;
        cin >> F[i];
    }

    for(int i = 0; i < n; i++)
    {
        int MaxIndex = MaxInColumn(A, i, n);
        long double Maximum = A[MaxIndex][i];
        if(abs(Maximum) < zero)
        {
            cout << "Матрица вырожденная " << endl;
            cont = false;
            break;
        }
        else if(MaxIndex != i)
        {
            for (int k = 0; k < n; k++) {
                swap(A[i][k], A[MaxIndex][k]);
                A[i][k] /= Maximum;
            }
            swap(F[i], F[MaxIndex]);
            F[i] /= Maximum;
        }
        else
        {
            for (int k = 0; k < n; k++) {
                A[i][k] /= Maximum;
            }
            F[i] /= Maximum;
        }
        if (cont == true) {
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    long double denominator = A[j][i];
                    for (int k = i; k < n; k++) {
                        A[j][k] -= A[i][k] * denominator;
                    }
                    F[j] -= F[i] * denominator;
                }
            }
        }
    }

    if(cont == true) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << A[i][j] << "\t";
            }
            cout << "|" << F[i];
            cout << endl;
        }
    }

    //system("pause");
    return 0;
}