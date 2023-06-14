#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int MaxInColumn(long double **A, int j, int n)
{
    int MaxIndex;
    for (int i = j; i < n; i++)
    {
        if (i == j)
            MaxIndex = i;
        else
        {
            if ((abs(A[MaxIndex][j])) < (abs(A[i][j])))
                MaxIndex = i;
        }
    }
    //cout << "В столбце " << j << " максимальный по модулю элемент не выше диагонали равен " << A[MaxIndex][j] << endl;
    return MaxIndex;
}

void MatrixMult(int n, long double **result, long double **left, long double **right)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            long double sum = 0;
            for (int k = 0; k < n; k++)
                sum += left[i][k] * right[k][j];
            result[i][j] = sum;
        }
}

void MatrixAdd(int n, long double **result, long double **left, long double **right)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = left[i][j] + right[i][j];
}

void MatrixDiff(int n, long double **result, long double **left, long double **right)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = left[i][j] - right[i][j];
}

int main()
{
    //setlocale(LC_ALL,"rus");
    system("chcp 65001");
    int n;
    bool cont = true;
    long double zero = 0.0000000001;
    cout << "Введите размерность матрицы: " << endl;
    cin >> n;
    auto **A = new long double*[n];
    auto **A2 = new long double*[n];
    auto **F = new long double*[n];
    cout << "Исходная матрица: " << endl;
    for (int i = 0; i < n; i++)
    {
        A[i] = new long double[n];
        A2[i] = new long double[n];
        F[i] = new long double[n];
        for(int j = 0; j < n; j++)
        {
            if (i == j)
                F[i][i] = 1;
            else
                F[i][j] = 0;
            //cout << "Введите элемент с индексом [" << i << ";" << j << "]: " << endl;
            //cin >> A[i][j];
            A[i][j] = rand() % 201 - 100;
            cout << A[i][j] << "\t";
            A2[i][j] = A[i][j];
        }
        cout << endl;
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
                swap(F[i][k], F[MaxIndex][k]);
                A[i][k] /= Maximum;
                F[i][k] /= Maximum;
            }
        }
        else
        {
            for (int k = 0; k < n; k++) {
                A[i][k] /= Maximum;
                F[i][k] /= Maximum;
            }
        }
        if (cont == true) {
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    long double denominator = A[j][i];
                    for (int kk = 0; kk < n; kk++)
                        F[j][kk] -= F[i][kk] * denominator;
                    for (int k = i; k < n; k++)
                        A[j][k] -= A[i][k] * denominator;

                }
            }
        }
    }

    if(cont == true) {
        cout << "Исходная матрица приведена к единичной: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << A[i][j] << "\t";
            }
            //cout << "|" << F[i];
            cout << endl;
        }
        cout << "Обратная матрица: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << F[i][j] << "\t";
            }
            //cout << "|" << F[i];
            cout << endl;
        }
    }

    auto **B = new long double*[n];
    for (int i = 0; i < n; i++)
        B[i] = new long double[n];

    long double accuracy = 0;
    MatrixMult(n, B, A2, F);

    for (int i = 0; i < n; i++)
        B[i][i]--;

    cout << "AX - E: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << B[i][j] << "\t";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            accuracy += abs(B[i][j]);

    cout << "Числовая характеристика матрицы X: " << accuracy << endl;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            F[i][j] += (F[i][j]/100) * (rand() % 11 - 10);
        }

    cout << "Обратная матрица с искажением +- 10%: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << F[i][j] << "\t";
        }
        //cout << "|" << F[i];
        cout << endl;
    }

    long double accuracy2 = 0;
    MatrixMult(n, B, A2, F);
    for (int i = 0; i < n; i++)
        B[i][i]--;

    cout << "AX - E (искажённая): " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << B[i][j] << "\t";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            accuracy2 += abs(B[i][j]);

    cout << "Числовая характеристика искажённой матрицы X: " << accuracy2 << endl;

    for(int i = 0; i < 5; i++)
    {
        accuracy2 = 0;
        auto **Xk = new long double*[n];
        auto **Xk2 = new long double*[n];
        auto **E2 = new long double*[n];
        for(int j = 0; j < n; j++) {
            Xk[j] = new long double[n];
            Xk2[j] = new long double[n];
            E2[j] = new long double[n];
        }

        for(int ii = 0; ii < n; ii++)
            for(int jj = 0; jj < n; jj++)
                if(ii == jj)
                    E2[ii][jj] = 2;
                else
                    E2[ii][jj] = 0;

        MatrixMult(n, Xk, A2, F);
        MatrixDiff(n, Xk, E2, Xk);
        MatrixMult(n, Xk2, F, Xk);
        for(int ii = 0; ii < n; ii++)
            for(int jj = 0; jj < n; jj++)
                F[ii][jj] = Xk2[ii][jj];

        MatrixMult(n, B, A2, F);
        for (int ii = 0; ii < n; ii++)
            B[ii][ii]--;

        for (int ii = 0; ii < n; ii++)
            for (int jj = 0; jj < n; jj++)
                accuracy2 += abs(B[ii][jj]);

        cout << "Числовая характеристика матрицы после шага " << i+1 << ": " << accuracy2 << endl;
    }

    cout << "Обратная матрица после приближения (5 итераций):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << F[i][j] << "\t";
        }
        cout << endl;
    }

    long double accuracy3 = 0;
    MatrixMult(n, B, A2, F);
    for (int i = 0; i < n; i++)
        B[i][i]--;

    cout << "AX - E (после приближения(5 циклов)): " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << B[i][j] << "\t";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            accuracy3 += abs(B[i][j]);

    cout << "Числовая характеристика матрицы после приближения: " << accuracy3 << endl;
    //system("pause");
    return 0;
}