#include "DynamicArray.h"
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <utility>

using namespace std;

void showByValue(DynamicArray<int> array, const int* originalData) {
    cout << "Получен массив: " << array << '\n';
    cout << "Адрес данных совпадает: " << (array.begin() == originalData) << '\n';
}

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

    cout << "\nЧасть 4\n";
    DynamicArray<int> values(2);
    values[0] = 10;
    values[1] = 20;
    const DynamicArray<int>& readOnly = values;
    cout << "Элемент по индексу 0: " << readOnly[0] << '\n';

    try {
        cout << readOnly[2] << '\n';
    } catch (const out_of_range& error) {
        cout << error.what() << '\n';
    }

    try {
        values[0] = 101;
    } catch (const invalid_argument& error) {
        cout << error.what() << '\n';
    }

    DynamicArray<int> same(values);
    cout << "Массивы равны: " << boolalpha << (values == same) << '\n';
    same[0] = same[1];
    cout << "Массивы различаются: " << (values != same) << '\n';

    values += b;
    cout << "После += массив: " << values << '\n';
    values -= b;
    cout << "После -= массив: " << values << '\n';

    values += 5;
    cout << "После += 5: " << values << '\n';
    values -= 5;
    cout << "После -= 5: " << values << '\n';

    for (auto& value : values) {
        ++value;
    }
    cout << "После изменения в цикле: ";
    for (const auto& value : readOnly) {
        cout << value << ' ';
    }
    cout << '\n';

    cout << "\nЧасть 5\n";
    DynamicArray<int> copy(1);
    copy = values;
    copy[0] = 7;
    cout << "После копирующего присваивания: " << copy << '\n';
    cout << "Исходный массив: " << values << '\n';

    const int* originalData = values.begin();
    cout << "Передача по значению, размер до вызова: " << values.size() << '\n';
    showByValue(values, originalData);
    cout << "Размер после копирования: " << values.size() << '\n';

    cout << "Передача с move, размер до вызова: " << values.size() << '\n';
    showByValue(std::move(values), originalData);
    cout << "Размер после перемещения: " << values.size() << '\n';

    DynamicArray<int> moved(1);
    moved = std::move(copy);
    cout << "После перемещающего присваивания: " << moved << '\n';
    cout << "Размер источника: " << copy.size() << '\n';
}
