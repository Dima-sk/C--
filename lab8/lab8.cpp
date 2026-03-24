#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

class Stroka {
private:
    char* str;
    int length;

public:
    // Конструкторы
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
    
    // Методы
    int dlina() const { return length; }
    
    // Перегруженные операторы потоков (дружественные функции)
    friend ostream& operator<<(ostream& os, const Stroka& s);
    friend istream& operator>>(istream& is, Stroka& s);
    
    // Методы для работы с файлами
    void saveToFile(ofstream& file) const {
        file.write((char*)&length, sizeof(length));
        file.write(str, length);
    }
    
    void loadFromFile(ifstream& file) {
        file.read((char*)&length, sizeof(length));
        delete[] str;
        str = new char[length + 1];
        file.read(str, length);
        str[length] = '\0';
    }
    
    // Методы изменения состояния объекта
    void toUpperCase() {
        for (int i = 0; i < length; i++) {
            if (str[i] >= 'a' && str[i] <= 'z')
                str[i] = str[i] - 'a' + 'A';
        }
    }
    
    void toLowerCase() {
        for (int i = 0; i < length; i++) {
            if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] = str[i] - 'A' + 'a';
        }
    }
    
    void reverse() {
        for (int i = 0; i < length / 2; i++) {
            char temp = str[i];
            str[i] = str[length - 1 - i];
            str[length - 1 - i] = temp;
        }
    }
    
    void append(const char* suffix) {
        int suffixLen = strlen(suffix);
        char* newStr = new char[length + suffixLen + 1];
        strcpy(newStr, str);
        strcat(newStr, suffix);
        delete[] str;
        str = newStr;
        length += suffixLen;
    }
    
    void clear() {
        delete[] str;
        str = new char[1];
        str[0] = '\0';
        length = 0;
    }
    
    // Геттер
    const char* c_str() const { return str; }
};

// Оператор вывода в поток
ostream& operator<<(ostream& os, const Stroka& s) {
    os << s.str;
    return os;
}

// Оператор ввода из потока
istream& operator>>(istream& is, Stroka& s) {
    char buffer[1000];
    is >> buffer;
    delete[] s.str;
    s.length = strlen(buffer);
    s.str = new char[s.length + 1];
    strcpy(s.str, buffer);
    return is;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "ЗАПИСЬ ОБЪЕКТОВ В ФАЙЛ" << endl;
    
    Stroka s1("Hello");
    Stroka s2("World");
    Stroka s3("C++");
    
    // Запись в текстовый файл с использованием оператора <<
    ofstream textFile("strings_text.txt");
    if (textFile.is_open()) {
        textFile << "Строка 1: " << s1 << endl;
        textFile << "Строка 2: " << s2 << endl;
        textFile << "Строка 3: " << s3 << endl;
        textFile << "Конкатенация: " << (s1 + s2) << endl;
        textFile.close();
        cout << "Объекты записаны в strings_text.txt" << endl;
    } else {
        cout << "Ошибка открытия файла!" << endl;
    }
    
    // Запись в бинарный файл
    ofstream binFile("strings_bin.dat", ios::binary);
    if (binFile.is_open()) {
        s1.saveToFile(binFile);
        s2.saveToFile(binFile);
        s3.saveToFile(binFile);
        binFile.close();
        cout << "Объекты записаны в strings_bin.dat (бинарный)" << endl;
    }
    
    cout << endl;
    
    cout << "ЧТЕНИЕ ОБЪЕКТОВ ИЗ ФАЙЛА" << endl;
    
    // Чтение из текстового файла
    ifstream readTextFile("strings_text.txt");
    if (readTextFile.is_open()) {
        cout << "Содержимое strings_text.txt:" << endl;
        string line;
        while (getline(readTextFile, line)) {
            cout << "  " << line << endl;
        }
        readTextFile.close();
    }
    
    // Чтение из бинарного файла
    ifstream readBinFile("strings_bin.dat", ios::binary);
    if (readBinFile.is_open()) {
        cout << "\nЧтение из strings_bin.dat:" << endl;
        Stroka r1, r2, r3;
        r1.loadFromFile(readBinFile);
        r2.loadFromFile(readBinFile);
        r3.loadFromFile(readBinFile);
        
        cout << "  Строка 1: " << r1 << endl;
        cout << "  Строка 2: " << r2 << endl;
        cout << "  Строка 3: " << r3 << endl;
        
        readBinFile.close();
    }
    
    cout << endl;

    cout << "РАБОТА С STRINGSTREAM" << endl;
    
    Stroka s4("Programming");
    Stroka s5("Language");
    
    // Создание строкового потока
    ostringstream oss;
    oss << "Язык: " << s5 << ", объект: " << s4;
    string result = oss.str();
    cout << "Результат ostringstream: " << result << endl;
    
    // Разбор строки
    istringstream iss("Hello World C++");
    Stroka w1, w2, w3;
    iss >> w1 >> w2 >> w3;
    
    cout << "Разбор строки:" << endl;
    cout << "  Слово 1: " << w1 << endl;
    cout << "  Слово 2: " << w2 << endl;
    cout << "  Слово 3: " << w3 << endl;
    
    cout << endl;
    
    cout << "ИЗМЕНЕНИЕ СОСТОЯНИЯ ОБЪЕКТОВ" << endl;
    
    Stroka s6("Hello World");
    cout << "Исходная строка: " << s6 << endl;
    
    // Изменение на верхний регистр
    s6.toUpperCase();
    cout << "После toUpperCase(): " << s6 << endl;
    
    // Изменение на нижний регистр
    s6.toLowerCase();
    cout << "После toLowerCase(): " << s6 << endl;
    
    // Реверс строки
    s6.reverse();
    cout << "После reverse(): " << s6 << endl;
    
    // Добавление текста
    s6.append(" - End");
    cout << "После append(\" - End\"): " << s6 << endl;
    
    // Очистка
    s6.clear();
    cout << "После clear(): '" << s6 << "' (длина: " << s6.dlina() << ")" << endl;
    
    cout << endl;

    cout << "КОМПЛЕКСНАЯ ДЕМОСТРАЦИЯ" << endl;
    
    // Создание массива строк
    Stroka strings[5] = {
        Stroka("First"),
        Stroka("Second"),
        Stroka("Third"),
        Stroka("Fourth"),
        Stroka("Fifth")
    };
    
    // Запись в файл
    ofstream outFile("demo.txt");
    for (int i = 0; i < 5; i++) {
        outFile << (i + 1) << ": " << strings[i] << endl;
    }
    outFile.close();
    
    // Чтение и модификация
    ifstream inFile("demo.txt");
    string line;
    int lineNum = 1;
    
    cout << "Обработка файла demo.txt:" << endl;
    while (getline(inFile, line)) {
        // Создаем строковый поток для разбора
        istringstream lineStream(line);
        string num, text;
        getline(lineStream, num, ':');
        getline(lineStream >> ws, text);
        
        Stroka temp(text.c_str());
        temp.toUpperCase();
        
        cout << "  Строка " << lineNum++ << ": " << temp << endl;
    }
    inFile.close();
    
    return 0;
}