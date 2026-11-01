#include "DynamicArray.h"
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <typeinfo>

using namespace std;

int main() {
    DynamicArray<int> a(2);
    a.set(0, 10);
    a.set(1, 20);
    DynamicArray<int> b(a);
    b.pushBack(30);
    a.add(b);
    cout << "После сложения: ";
    a.print();
    a.sub(b);
    cout << "После вычитания: ";
    a.print();

    try {
        a.get(10);
    } catch (const out_of_range& error) {
        cout << "Индекс вне границ: " << error.what() << '\n';
    }

    try {
        a.set(0, 101);
    } catch (const invalid_argument& error) {
        cout << "Недопустимое значение: " << error.what() << '\n';
    }

    try {
        // Имитируем неудачное выделение памяти для демонстрации типа исключения.
        throw bad_alloc();
    } catch (const bad_alloc&) {
        cout << "Обработано bad_alloc\n";
    }

    DynamicArray<int> numbers1(3);
    numbers1.set(0, 1);
    numbers1.set(1, 2);
    numbers1.set(2, 3);

    DynamicArray<int> numbers2(3);
    numbers2.set(0, 4);
    numbers2.set(1, 6);
    numbers2.set(2, 3);

    cout << "Числовой массив: " << numbers1 << '\n';
    cout << "Расстояние между числовыми массивами: "
              << numbers1.distance(numbers2) << '\n';

    DynamicArray<string> words(2);
    words.set(0, "привет");
    words.set(1, "мир");
    cout << "Строковый массив: " << words << '\n';

    try {
        words.distance(words);
    } catch (const bad_typeid&) {
        cout << "Расстояние для строк не поддерживается\n";
    }

    DynamicArray<int> shortArray(1);
    try {
        numbers1.distance(shortArray);
    } catch (const invalid_argument& error) {
        cout << "Размеры массивов не совпадают: " << error.what() << '\n';
    }
}
