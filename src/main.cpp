#include "DynamicArray.h"
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <typeinfo>

int main() {
    DynamicArray<int> a(2);
    a.set(0, 10);
    a.set(1, 20);
    DynamicArray<int> b(a);
    b.pushBack(30);
    a.add(b);
    std::cout << "После сложения: ";
    a.print();
    a.sub(b);
    std::cout << "После вычитания: ";
    a.print();

    try {
        a.get(10);
    } catch (const std::out_of_range& error) {
        std::cout << "Индекс вне границ: " << error.what() << '\n';
    }

    try {
        a.set(0, 101);
    } catch (const std::invalid_argument& error) {
        std::cout << "Недопустимое значение: " << error.what() << '\n';
    }

    try {
        // Имитируем неудачное выделение памяти для демонстрации типа исключения.
        throw std::bad_alloc();
    } catch (const std::bad_alloc&) {
        std::cout << "Обработано std::bad_alloc\n";
    }

    DynamicArray<int> numbers1(3);
    numbers1.set(0, 1);
    numbers1.set(1, 2);
    numbers1.set(2, 3);

    DynamicArray<int> numbers2(3);
    numbers2.set(0, 4);
    numbers2.set(1, 6);
    numbers2.set(2, 3);

    std::cout << "Числовой массив: " << numbers1 << '\n';
    std::cout << "Расстояние между числовыми массивами: "
              << numbers1.distance(numbers2) << '\n';

    DynamicArray<std::string> words(2);
    words.set(0, "привет");
    words.set(1, "мир");
    std::cout << "Строковый массив: " << words << '\n';

    try {
        words.distance(words);
    } catch (const std::bad_typeid&) {
        std::cout << "Расстояние для строк не поддерживается\n";
    }

    DynamicArray<int> shortArray(1);
    try {
        numbers1.distance(shortArray);
    } catch (const std::invalid_argument& error) {
        std::cout << "Размеры массивов не совпадают: " << error.what() << '\n';
    }
}
