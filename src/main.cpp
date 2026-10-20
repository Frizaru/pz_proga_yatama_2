#include "DynamicArray.h"
#include <iostream>
#include <new>
#include <stdexcept>

int main() {
    DynamicArray a(2);
    a.set(0, 10);
    a.set(1, 20);
    DynamicArray b(a);
    b.pushBack(30);
    a.add(b);
    a.sub(b);
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
}
