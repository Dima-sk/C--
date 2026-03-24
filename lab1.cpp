#include <iostream>
#include <windows.h>
using namespace std;

// ========== ЗАДАЧА 1 ==========
int power(int x, int n) {
    int p = 1;
    for(int i = 0; i < n; i++) {
        p *= x;
    }
    return p;
}

void task1() {
    cout << "\n========== ЗАДАЧА 1 ==========" << endl;
    cout << "Вычисление степени числа 2:" << endl;
    
    for(int i = 0; i < 10; i++) {
        cout << "2^" << i << " = " << power(2, i) << endl;
    }
}

// ========== ЗАДАЧА 2 ==========
void task2() {
    cout << "\n========== ЗАДАЧА 2 ==========" << endl;
    cout << "Операции с указателями:" << endl;
    
    int mass[] = {100, 200, 300};
    int *ptr1 = mass;
    int *ptr2 = &mass[2];
    
    cout << "Начальные значения:" << endl;
    cout << "*ptr1 = " << *ptr1 << ", *ptr2 = " << *ptr2 << endl;
    cout << "Разность указателей: ptr2 - ptr1 = " << (ptr2 - ptr1) << endl;
    
    ptr1++;
    cout << "После ptr1++: *ptr1 = " << *ptr1 << endl;
    
    ++ptr2;
    cout << "После ++ptr2: ptr2 указывает за массив" << endl;
    cout << "ptr2 - ptr1 = " << (ptr2 - ptr1) << endl;
}

// ========== ЗАДАЧА 3 ==========
void obmen1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void obmen2(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void obmen3(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void task3() {
    cout << "\n========== ЗАДАЧА 3 ==========" << endl;
    cout << "Обмен значений тремя способами:" << endl;
    
    int a, b;
    
    // Способ 1
    a = 2; b = 5;
    cout << "\n1. Передача по значению (obmen1):" << endl;
    cout << "   До: a = " << a << ", b = " << b << endl;
    obmen1(a, b);
    cout << "   После: a = " << a << ", b = " << b << " (не работает!)" << endl;
    
    // Способ 2
    a = 2; b = 5;
    cout << "\n2. Передача по указателю (obmen2):" << endl;
    cout << "   До: a = " << a << ", b = " << b << endl;
    obmen2(&a, &b);
    cout << "   После: a = " << a << ", b = " << b << endl;
    
    // Способ 3
    a = 2; b = 5;
    cout << "\n3. Передача по ссылке (obmen3):" << endl;
    cout << "   До: a = " << a << ", b = " << b << endl;
    obmen3(a, b);
    cout << "   После: a = " << a << ", b = " << b << endl;
}

// ========== MAIN ==========
int main() {
    setlocale(LC_ALL, "Russian");
    
    
    task1();
    task2();
    task3();
    
    
    return 0;
}