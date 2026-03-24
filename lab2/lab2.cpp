#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

const int N = 5;

void fillMatrix(double a[N][N]) {
    srand((unsigned)time(0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = rand() % 100 / 10.0;
}

void printMatrix(double a[N][N]) {
    cout << "\nМатрица:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(8) << fixed << setprecision(2) << a[i][j];
        cout << endl;
    }
}

double maxMatrix(double a[N][N]) {
    double mx = a[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a[i][j] > mx) mx = a[i][j];
    return mx;
}

double minMatrix(double a[N][N]) {
    double mn = a[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a[i][j] < mn) mn = a[i][j];
    return mn;
}

double maxUpperTri(double a[N][N]) {
    double mx = a[0][0];
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            if (a[i][j] > mx) mx = a[i][j];
    return mx;
}

double minUpperTri(double a[N][N]) {
    double mn = a[0][0];
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            if (a[i][j] < mn) mn = a[i][j];
    return mn;
}

double maxLowerTri(double a[N][N]) {
    double mx = a[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (a[i][j] > mx) mx = a[i][j];
    return mx;
}

double minLowerTri(double a[N][N]) {
    double mn = a[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (a[i][j] < mn) mn = a[i][j];
    return mn;
}

double maxMainDiag(double a[N][N]) {
    double mx = a[0][0];
    for (int i = 0; i < N; i++)
        if (a[i][i] > mx) mx = a[i][i];
    return mx;
}

double minMainDiag(double a[N][N]) {
    double mn = a[0][0];
    for (int i = 0; i < N; i++)
        if (a[i][i] < mn) mn = a[i][i];
    return mn;
}

double maxSideDiag(double a[N][N]) {
    double mx = a[0][N - 1];
    for (int i = 0; i < N; i++)
        if (a[i][N - 1 - i] > mx) mx = a[i][N - 1 - i];
    return mx;
}

double minSideDiag(double a[N][N]) {
    double mn = a[0][N - 1];
    for (int i = 0; i < N; i++)
        if (a[i][N - 1 - i] < mn) mn = a[i][N - 1 - i];
    return mn;
}

double avgAll(double a[N][N]) {
    double sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += a[i][j];
    return sum / (N * N);
}

double avgUpperTri(double a[N][N]) {
    double sum = 0;
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++) {
            sum += a[i][j];
            count++;
        }
    return sum / count;
}

double avgLowerTri(double a[N][N]) {
    double sum = 0;
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++) {
            sum += a[i][j];
            count++;
        }
    return sum / count;
}

void rowSums(double a[N][N]) {
    cout << "\nСуммы строк:\n";
    for (int i = 0; i < N; i++) {
        double sum = 0;
        for (int j = 0; j < N; j++) sum += a[i][j];
        cout << "Строка " << i + 1 << ": " << sum << endl;
    }
}

void colSums(double a[N][N]) {
    cout << "\nСуммы столбцов:\n";
    for (int j = 0; j < N; j++) {
        double sum = 0;
        for (int i = 0; i < N; i++) sum += a[i][j];
        cout << "Столбец " << j + 1 << ": " << sum << endl;
    }
}

void rowMinsMaxs(double a[N][N]) {
    cout << "\nМинимумы и максимумы строк:\n";
    for (int i = 0; i < N; i++) {
        double mn = a[i][0], mx = a[i][0];
        for (int j = 1; j < N; j++) {
            if (a[i][j] < mn) mn = a[i][j];
            if (a[i][j] > mx) mx = a[i][j];
        }
        cout << "Строка " << i + 1 << ": min = " << mn << ", max = " << mx << endl;
    }
}

void colMinsMaxs(double a[N][N]) {
    cout << "\nМинимумы и максимумы столбцов:\n";
    for (int j = 0; j < N; j++) {
        double mn = a[0][j], mx = a[0][j];
        for (int i = 1; i < N; i++) {
            if (a[i][j] < mn) mn = a[i][j];
            if (a[i][j] > mx) mx = a[i][j];
        }
        cout << "Столбец " << j + 1 << ": min = " << mn << ", max = " << mx << endl;
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    double a[N][N];
    fillMatrix(a);
    printMatrix(a);

    cout << "\nМаксимум матрицы: " << maxMatrix(a) << endl;
    cout << "Минимум матрицы: " << minMatrix(a) << endl;
    cout << "Максимум верхнетреугольной части: " << maxUpperTri(a) << endl;
    cout << "Минимум верхнетреугольной части: " << minUpperTri(a) << endl;
    cout << "Максимум нижнетреугольной части: " << maxLowerTri(a) << endl;
    cout << "Минимум нижнетреугольной части: " << minLowerTri(a) << endl;
    cout << "Максимум главной диагонали: " << maxMainDiag(a) << endl;
    cout << "Минимум главной диагонали: " << minMainDiag(a) << endl;
    cout << "Максимум побочной диагонали: " << maxSideDiag(a) << endl;
    cout << "Минимум побочной диагонали: " << minSideDiag(a) << endl;
    cout << "Среднее всей матрицы: " << avgAll(a) << endl;
    cout << "Среднее верхнетреугольной части: " << avgUpperTri(a) << endl;
    cout << "Среднее нижнетреугольной части: " << avgLowerTri(a) << endl;

    rowSums(a);
    colSums(a);
    rowMinsMaxs(a);
    colMinsMaxs(a);

    return 0;
}