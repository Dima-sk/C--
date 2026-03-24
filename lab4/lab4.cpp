#include <iostream>
#include <cstring>
#include <windows.h>
using namespace std;

int main() {
    // Настройка кодировки для корректного отображения кириллицы
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    char source1[80] = "qwerty";
    char source2[] = "1234567890";

    cout << "=== СТАТИЧЕСКИЕ СТРОКИ ===" << endl;
    cout << "source1 = " << source1 << endl;
    cout << "source2 = " << source2 << endl;

    // Получение длины строк
    cout << "\nДлина source1 = " << strlen(source1) << " символов" << endl;
    cout << "Длина source2 = " << strlen(source2) << " символов" << endl;

    // Сравнение строк
    int compareResult = strcmp(source1, source2);
    cout << "\nРезультат strcmp(source1, source2) = " << compareResult << endl;
    if (compareResult < 0) {
        cout << "  → source1 < source2" << endl;
    } else if (compareResult > 0) {
        cout << "  → source1 > source2" << endl;
    } else {
        cout << "  → source1 = source2" << endl;
    }

    // Копирование строки
    char copy1[100];
    strcpy(copy1, source1);
    cout << "\nКопия source1 (strcpy): " << copy1 << endl;

    strcat(source1, source2);
    cout << "После сцепления source1 + source2 (strcat):" << endl;
    cout << "  source1 = " << source1 << endl;
    
    cout << "\n=== ДИНАМИЧЕСКИЕ СТРОКИ ===" << endl;

    // Выделение памяти в динамической области
    char* dynamic1 = new char[100];
    char* dynamic2 = new char[100];

    // Инициализация строк
    strcpy(dynamic1, "динамическая_строка_1");
    strcpy(dynamic2, "динамическая_строка_2");

    cout << "dynamic1 = " << dynamic1 << endl;
    cout << "dynamic2 = " << dynamic2 << endl;

    cout << "\nДлина dynamic1 = " << strlen(dynamic1) << " символов" << endl;
    
    int compareDyn = strcmp(dynamic1, dynamic2);
    cout << "Результат strcmp(dynamic1, dynamic2) = " << compareDyn << endl;

    // Конкатенация строк
    strcat(dynamic1, dynamic2);
    cout << "После strcat(dynamic1, dynamic2):" << endl;
    cout << "  dynamic1 = " << dynamic1 << endl;

    // Освобождение динамической памяти
    delete[] dynamic1;
    delete[] dynamic2;
    return 0;
}