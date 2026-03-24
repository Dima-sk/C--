#include <iostream>
#include <windows.h>
using namespace std;

// Вывод массива на экран
void printArray(int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Сортировка выбором (весь массив)
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        // Поиск минимального элемента в неотсортированной части
        int minPos = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minPos]) {
                minPos = j;
            }
        }
        // Обмен текущего элемента с минимальным
        if (minPos != i) {
            int temp = arr[i];
            arr[i] = arr[minPos];
            arr[minPos] = temp;
        }
    }
}

// Сортировка пузырьком (диапазон [left, right]
void bubbleSortRange(int arr[], int left, int right, bool ascending = true) {
    for (int i = left; i < right; i++) {
        for (int j = left; j < right - (i - left); j++) {
            bool needSwap = false;
            
            if (ascending) {
                // По возрастанию: меняем если левый > правого
                if (arr[j] > arr[j + 1]) needSwap = true;
            } else {
                // По убыванию: меняем если левый < правого
                if (arr[j] < arr[j + 1]) needSwap = true;
            }
            
            if (needSwap) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Сортировка вставками (диапазон [left, right])
void insertionSortRange(int arr[], int left, int right, bool ascending = true) {
    for (int i = left + 1; i <= right; i++) {
        int current = arr[i];  // Элемент для вставки
        int j = i - 1;
        
        // Сдвигаем элементы вправо пока не найдём правильное место
        while (j >= left) {
            bool needShift = false;
            
            if (ascending) {
                if (arr[j] > current) needShift = true;
            } else {
                if (arr[j] < current) needShift = true;
            }
            
            if (needShift) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = current;
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int original[] = {2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9};
    int size = sizeof(original) / sizeof(original[0]);

    cout << "Исходный массив (" << size << " элементов):" << endl;
    printArray(original, size);
    cout << endl;

    // ========== ТЕСТ 1: Сортировка выбором ==========
    int arr1[100];
    for (int i = 0; i < size; i++) arr1[i] = original[i];
    
    selectionSort(arr1, size);
    cout << "1. Сортировка выбором (весь массив):" << endl;
    printArray(arr1, size);
    cout << endl;

    // ========== ТЕСТ 2: Сортировка пузырьком ==========
    int arr2[100];
    for (int i = 0; i < size; i++) arr2[i] = original[i];
    
    bubbleSortRange(arr2, 0, size - 1, true);
    cout << "2. Сортировка пузырьком (весь массив, по возрастанию):" << endl;
    printArray(arr2, size);
    cout << endl;

    // ========== ТЕСТ 3-5: Сортировка диапазона [2, 8] ==========
    int left = 2, right = 8;
    cout << "3-5. Сортировка диапазона [" << left << ", " << right << "]:" << endl;
    cout << "   Элементы диапазона: ";
    for (int i = left; i <= right; i++) {
        cout << original[i] << " ";
    }
    cout << endl << endl;

    // Сортировка вставками (по возрастанию)
    int arr3[100];
    for (int i = 0; i < size; i++) arr3[i] = original[i];
    
    insertionSortRange(arr3, left, right, true);
    cout << "3.1 Вставками (по возрастанию):" << endl;
    printArray(arr3, size);
    cout << endl;

    // Сортировка пузырьком (по возрастанию)
    int arr4[100];
    for (int i = 0; i < size; i++) arr4[i] = original[i];
    
    bubbleSortRange(arr4, left, right, true);
    cout << "3.2 Пузырьком (по возрастанию):" << endl;
    printArray(arr4, size);
    cout << endl;

    // Сортировка пузырьком (по убыванию)
    int arr5[100];
    for (int i = 0; i < size; i++) arr5[i] = original[i];
    
    bubbleSortRange(arr5, left, right, false);
    cout << "3.3 Пузырьком (по убыванию):" << endl;
    printArray(arr5, size);
    cout << endl;

    return 0;
}