#include <iostream>
#include <cstring>
using namespace std;

// 9.1.1 
// Шаблон функции Sort
template <typename T>
void Sort(T mas[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (mas[j] > mas[j + 1]) {
                T temp = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = temp;
            }
        }
    }
}

// Класс Money для демонстрации Sort с пользовательским типом
class Money {
private:
    long dollars;
    int cents;

public:
    Money() : dollars(0), cents(0) {}
    
    Money(long d, int c) : dollars(d), cents(c) {}
    
    // Перегрузка оператора > (обязательно для Sort)
    bool operator>(const Money& amt) const {
        return (dollars > amt.dollars) || 
               ((dollars == amt.dollars) && (cents > amt.cents));
    }
    
    // Перегрузка оператора <
    bool operator<(const Money& amt) const {
        return (dollars < amt.dollars) || 
               ((dollars == amt.dollars) && (cents < amt.cents));
    }
    
    // Оператор вывода (дружественная функция)
    friend ostream& operator<<(ostream& os, const Money& amt);
    
    // Геттеры
    long getDollars() const { return dollars; }
    int getCents() const { return cents; }
};

ostream& operator<<(ostream& os, const Money& amt) {
    os << "$" << amt.dollars << "." << amt.cents;
    return os;
}

// 9.1.2 
// Шаблон 1: Возвращает больший из двух параметров
template <typename T>
T getmax(T t1, T t2) {
    return t1 > t2 ? t1 : t2;
}

// Шаблон 2: Возвращает максимальный элемент массива
template <typename T>
T getmax(T t[], size_t size) {
    T retval = t[0];
    for (size_t i = 1; i < size; i++) {
        if (t[i] > retval) {
            retval = t[i];
        }
    }
    return retval;
}

// 9.1.3 
// Специализация для char* (строк C-стиля)
char* getmax(char* s1, char* s2) {
    return strcmp(s1, s2) > 0 ? s1 : s2;
}

// Специализация для const char*
const char* getmax(const char* s1, const char* s2) {
    return strcmp(s1, s2) > 0 ? s1 : s2;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "9.1.1 СОРТИРОВКА ЦЕЛЫХ ЧИСЕЛ" << endl;
    
    int mas1[] = {10, 20, 30, 11, 25, 32, 0};
    int size1 = sizeof(mas1) / sizeof(mas1[0]);
    
    cout << "До сортировки: ";
    for (int i = 0; i < size1; i++) {
        cout << mas1[i] << " ";
    }
    cout << endl;
    
    Sort(mas1, size1);
    
    cout << "После сортировки: ";
    for (int i = 0; i < size1; i++) {
        cout << mas1[i] << " ";
    }
    cout << endl << endl;
    
    cout << "9.1.1 СОРТИРОВКА ОБЪЕКТОВ Money" << endl;
    
    Money mas2[] = {
        Money(19, 10),
        Money(99, 99),
        Money(98, 95),
        Money(19, 95)
    };
    
    int size2 = sizeof(mas2) / sizeof(mas2[0]);
    
    cout << "До сортировки: ";
    for (int i = 0; i < size2; i++) {
        cout << mas2[i] << "  ";
    }
    cout << endl;
    
    Sort(mas2, size2);
    
    cout << "После сортировки: ";
    for (int i = 0; i < size2; i++) {
        cout << mas2[i] << "  ";
    }
    cout << endl << endl;
    
    //  9.1.2: Перегрузка getmax (целые числа) 
    cout << "9.1.2 ПЕРЕГРУЗКА getmax" << endl;
    
    int i1 = 3, i2 = 5;
    cout << "getmax(" << i1 << ", " << i2 << ") = " << getmax(i1, i2) << endl;
    
    int mas3[] = {3, 9, 5, 8};
    int size3 = sizeof(mas3) / sizeof(mas3[0]);
    cout << "getmax(массив) = " << getmax(mas3, size3) << endl;
    cout << "getmax(size) = " << getmax(size3) << endl << endl;
    
    //  9.1.2: getmax с вещественными числами 
    cout << "getmax с double:" << endl;
    double d1 = 3.14, d2 = 2.71;
    cout << "getmax(" << d1 << ", " << d2 << ") = " << getmax(d1, d2) << endl;
    
    double mas4[] = {1.5, 3.7, 2.1, 9.9};
    int size4 = sizeof(mas4) / sizeof(mas4[0]);
    cout << "getmax(массив double) = " << getmax(mas4, size4) << endl << endl;
    
    //  9.1.3: Специализация для строк 
    cout << "9.1.3 СПЕЦИАЛИЗАЦИЯ ДЛЯ СТРОК" << endl;
    cout << "----------------------------------------" << endl;
    
    char* s1 = (char*)"строка1";
    char* s2 = (char*)"строка2";
    
    cout << "getmax(\"строка1\", \"строка2\") = " << getmax(s1, s2) << endl;
    
    const char* s3 = "apple";
    const char* s4 = "banana";
    
    cout << "getmax(\"apple\", \"banana\") = " << getmax(s3, s4) << endl;
    
    // Массив строк
    char* strmas[] = {(char*)"cat", (char*)"dog", (char*)"bird"};
    // Для массива строк нужна отдельная функция
    cout << "\n(Для массива строк требуется отдельная специализация)" << endl << endl;
    
    return 0;
}