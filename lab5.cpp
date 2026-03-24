#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <windows.h>
using namespace std;

// Просмотр содержимого файла 
void viewFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Ошибка: файл не открыт!" << endl;
        return;
    }
    
    cout << "\n=== СОДЕРЖИМОЕ ФАЙЛА ===" << endl;
    char ch;
    while (fin.get(ch)) {
        cout << ch;
    }
    cout << "\n=== КОНЕЦ ФАЙЛА ===" << endl;
    fin.close();
}

// Подсчет пустых и непустых символов
void countEmptyNonEmptyChars(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Ошибка: файл не открыт!" << endl;
        return;
    }
    
    int emptyChars = 0;   // пробелы, табуляция, переводы строк, управляющие
    int nonEmptyChars = 0; // видимые символы
    char ch;
    
    while (fin.get(ch)) {
        if (isspace(static_cast<unsigned char>(ch)) || iscntrl(static_cast<unsigned char>(ch))) {
            emptyChars++;
        } else {
            nonEmptyChars++;
        }
    }
    
    cout << "\n=== СТАТИСТИКА СИМВОЛОВ ===" << endl;
    cout << "Пустых символов (пробелы, табуляция, управляющие): " << emptyChars << endl;
    cout << "Непустых символов (видимые): " << nonEmptyChars << endl;
    cout << "Всего символов: " << (emptyChars + nonEmptyChars) << endl;
    
    fin.close();
}

//Поиск подстроки в файле с записью результатов в отдельный файл
void searchSubstring(const string& filename, const string& substring, const string& resultFile) {
    ifstream fin(filename);
    ofstream fout(resultFile);
    
    if (!fin) {
        cout << "Ошибка: исходный файл не открыт!" << endl;
        return;
    }
    if (!fout) {
        cout << "Ошибка: файл результатов не открыт!" << endl;
        fin.close();
        return;
    }
    
    string line;
    int lineNumber = 0;
    int totalFound = 0;
    
    fout << "=== РЕЗУЛЬТАТЫ ПОИСКА ПОДСТРОКИ: \"" << substring << "\" ===" << endl << endl;
    
    while (getline(fin, line)) {
        lineNumber++;
        size_t pos = 0;
        int foundInLine = 0;
        
        while ((pos = line.find(substring, pos)) != string::npos) {
            foundInLine++;
            totalFound++;
            fout << "Найдено в строке " << lineNumber 
                 << ", позиция: " << (pos + 1) << endl;
            pos += substring.length();
        }
        
        if (foundInLine > 0) {
            fout << "  Строка " << lineNumber << ": " << line << endl;
        }
    }
    
    fout << "\n=== ИТОГО ===" << endl;
    fout << "Всего найдено вхождений: " << totalFound << endl;
    fout << "Поиск завершен." << endl;
    
    cout << "\nРезультаты поиска сохранены в файле: " << resultFile << endl;
    cout << "Всего найдено вхождений: " << totalFound << endl;
    
    fin.close();
    fout.close();
}

// Перенос номеров страниц из первой в последнюю
void movePageNumbers(const string& inputFile, const string& outputFile) {
    ifstream fin(inputFile);
    ofstream fout(outputFile);
    
    if (!fin || !fout) {
        cout << "Ошибка открытия файлов!" << endl;
        return;
    }
    
    string line;
    int pageNum = 1;
    bool firstLineOfPage = true;
    string pageNumberStr;
    
    while (getline(fin, line)) {
        // Проверка на признак новой страницы 
        if (!line.empty() && line[0] == '\f') {
            // Записываем номер предыдущей страницы в последнюю строку
            if (!pageNumberStr.empty()) {
                fout << pageNumberStr << endl;
            }
            
            firstLineOfPage = true;
            pageNum++;
            continue;
        }
        
        // Первая строка страницы - это номер страницы
        if (firstLineOfPage) {
            pageNumberStr = "";
            for (char c : line) {
                if (isdigit(c)) {
                    pageNumberStr += c;
                }
            }
            
            if (!pageNumberStr.empty()) {
                fout << "Страница " << pageNum << ":" << endl;
            }
            firstLineOfPage = false;
        } else {
            fout << line << endl;
        }
    }
    
    // Записываем номер последней страницы
    if (!pageNumberStr.empty()) {
        fout << pageNumberStr << endl;
    }
    
    cout << "\nФайл обработан. Результат в файле: " << outputFile << endl;
    cout << "Всего страниц: " << pageNum << endl;
    
    fin.close();
    fout.close();
}

//  Шифрование файла с использованием XOR
void encryptFile(const string& inputFile, const string& outputFile, const string& key) {
    ifstream fin(inputFile, ios::binary);
    ofstream fout(outputFile, ios::binary);
    
    if (!fin || !fout) {
        cout << "Ошибка открытия файлов!" << endl;
        return;
    }
    
    if (key.empty()) {
        cout << "Ошибка: ключ шифрования пуст!" << endl;
        return;
    }
    
    char ch;
    size_t keyIndex = 0;
    int charCount = 0;
    
    while (fin.get(ch)) {
        // XOR шифрование: c = c ^ key[i]
        char encrypted = ch ^ key[keyIndex];
        fout.put(encrypted);
        
        // Переход к следующему символу ключа
        keyIndex = (keyIndex + 1) % key.length();
        charCount++;
    }
    
    cout << "\nФайл зашифрован!" << endl;
    cout << "Результат в файле: " << outputFile << endl;
    cout << "Обработано символов: " << charCount << endl;
    cout << "Ключ шифрования: " << key << endl;
    
    fin.close();
    fout.close();
}

int main(int argc, char* argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    // Проверка аргументов командной строки для шифрования
    if (argc >= 4) {
        // Режим шифрования из командной строки
        string mode = argv[1];
        string inFile = argv[2];
        string outFile = argv[3];
        string key = (argc > 4) ? argv[4] : "default";
        
        cout << "Режим: " << mode << endl;
        cout << "Входной файл: " << inFile << endl;
        cout << "Выходной файл: " << outFile << endl;
        cout << "Ключ: " << key << endl << endl;
        
        if (mode == "-encrypt" || mode == "-e") {
            encryptFile(inFile, outFile, key);
        } else if (mode == "-view" || mode == "-v") {
            viewFile(inFile);
        } else if (mode == "-count" || mode == "-c") {
            countEmptyNonEmptyChars(inFile);
        } else {
            cout << "Неизвестный режим: " << mode << endl;
            cout << "Доступные режимы:" << endl;
            cout << "  -view <file>              - просмотр файла" << endl;
            cout << "  -count <file>             - подсчет символов" << endl;
            cout << "  -search <file> <sub> <out> - поиск подстроки" << endl;
            cout << "  -pages <in> <out>         - обработка номеров страниц" << endl;
            cout << "  -encrypt <in> <out> <key> - шифрование файла" << endl;
        }
        
        return 0;
    }
    string filename = "text.txt";
    
    // Демонстрация всех функций
    cout << "1. ПРОСМОТР ФАЙЛА" << endl;
    viewFile(filename);
    
    cout << "\n2. ПОДСЧЕТ СИМВОЛОВ" << endl;
    countEmptyNonEmptyChars(filename);
    
    cout << "\n3. ПОИСК ПОДСТРОКИ" << endl;
    string searchStr = "слово";
    searchSubstring(filename, searchStr, "search_results.txt");
    
    cout << "\n4. ОБРАБОТКА НОМЕРОВ СТРАНИЦ" << endl;
    movePageNumbers(filename, "pages_processed.txt");
    
    cout << "\n5. ШИФРОВАНИЕ ФАЙЛА" << endl;
    string key = "secret";
    encryptFile(filename, "encrypted.txt", key);
    
    // Проверка шифрования
    cout << "\n6. ПРОВЕРКА ШИФРОВАНИЯ (расшифровка)" << endl;
    encryptFile("encrypted.txt", "decrypted.txt", key);
    cout << "Расшифрованный файл: decrypted.txt" << endl;
    return 0;
}