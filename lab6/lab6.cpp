#include <iostream>
#include <cstring>
using namespace std;

class Stroka {
private:
    char* str;
    int length;

public:
    // Конструкторы и деструктор
    Stroka(const char* s = "") {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }
    
    Stroka(const Stroka& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }
    
    ~Stroka() { delete[] str; }
    
    // Оператор присваивания
    Stroka& operator=(const Stroka& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        return *this;
    }
    
    // Операторы
    Stroka operator+(const Stroka& other) const {
        Stroka result;
        delete[] result.str;
        result.length = length + other.length;
        result.str = new char[result.length + 1];
        strcpy(result.str, str);
        strcat(result.str, other.str);
        return result;
    }
    
    bool operator==(const Stroka& other) const {
        return strcmp(str, other.str) == 0;
    }
    
    bool operator!=(const Stroka& other) const {
        return !(*this == other);
    }
    
    char& operator[](int index) {
        if (index < 0) index = 0;
        if (index >= length) index = length - 1;
        return str[index];
    }
    
    // Методы
    int dlina() const { return length; }
    
    void vvod() {
        char buffer[1000];
        cin.getline(buffer, 1000);
        delete[] str;
        length = strlen(buffer);
        str = new char[length + 1];
        strcpy(str, buffer);
    }
    
    void vyvod() const { cout << str; }
    
    const char* c_str() const { return str; }
};

// Главная программа
int main() {
    setlocale(LC_ALL, "Russian");
    
    // Конструкторы
    cout << "1. Конструкторы:\n";
    Stroka s1;
    cout << "s1 (пустая): "; s1.vyvod(); cout << endl;
    
    Stroka s2("Hello");
    cout << "s2 (\"Hello\"): "; s2.vyvod(); cout << " (длина: " << s2.dlina() << ")\n";
    
    Stroka s3(s2);
    cout << "s3 (копия s2): "; s3.vyvod(); cout << endl << endl;
    
    //Присваивание
    cout << "2. Присваивание:\n";
    Stroka s4;
    s4 = s2;
    cout << "s4 = s2: "; s4.vyvod(); cout << endl << endl;
    
    //Конкатенация
    cout << "3. Конкатенация:\n";
    Stroka s5("Hello, ");
    Stroka s6("World!");
    Stroka s7 = s5 + s6;
    cout << "s5 + s6 = "; s7.vyvod(); 
    cout << " (длина: " << s7.dlina() << ")\n\n";
    
    //Сравнение
    cout << "4. Сравнение:\n";
    Stroka s8("test");
    Stroka s9("test");
    Stroka s10("TEST");
    cout << "s8 == s9: " << (s8 == s9 ? "равны" : "не равны") << endl;
    cout << "s8 == s10: " << (s8 == s10 ? "равны" : "не равны") << endl << endl;
    
    //Доступ к символам
    cout << "5. Доступ к символам:\n";
    Stroka s11("Programming");
    cout << "s11: "; s11.vyvod(); cout << endl;
    cout << "s11[0] = '" << s11[0] << "', s11[3] = '" << s11[3] << "'\n";
    s11[0] = 'p';
    cout << "После изменения: "; s11.vyvod(); cout << endl << endl;
    
    //Ввод
    cout << "6. Ввод с клавиатуры:\n";
    Stroka s12;
    cout << "Введите строку: ";
    s12.vvod();
    cout << "Вы ввели: "; s12.vyvod(); 
    cout << " (длина: " << s12.dlina() << ")\n\n";
    
    //Сложные операции
    cout << "7. Сложные операции:\n";
    Stroka s13 = Stroka("C++") + Stroka(" ") + Stroka("Programming");
    cout << "Результат: "; s13.vyvod(); cout << endl;
    
    return 0;
}