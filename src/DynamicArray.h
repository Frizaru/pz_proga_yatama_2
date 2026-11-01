#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

using namespace std;

template <typename T>
class DynamicArray {
    T* data;
    int count;

    void checkValue(T value) const {
        if constexpr (is_integral_v<T>) {
            bool wrongValue = value > 100;
            if constexpr (is_signed_v<T>) {
                wrongValue = wrongValue || value < -100;
            }
            if (wrongValue) {
                throw invalid_argument("Значение должно быть от -100 до 100");
            }
        }
    }

public:
    DynamicArray(int size) : data(new T[size]{}), count(size) {}

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray& other) : data(new T[other.count]), count(other.count) {
        for (int i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }

    int size() const {
        return count;
    }

    T get(int i) const {
        if (i < 0 || i >= count) {
            throw out_of_range("Индекс вне границ массива");
        }
        return data[i];
    }

    void set(int i, T value) {
        if (i < 0 || i >= count) {
            throw out_of_range("Индекс вне границ массива");
        }
        checkValue(value);
        data[i] = value;
    }

    void pushBack(T value) {
        checkValue(value);
        T* newData = new T[count + 1];
        for (int i = 0; i < count; ++i) {
            newData[i] = data[i];
        }
        newData[count] = value;
        delete[] data;
        data = newData;
        ++count;
    }

    void add(const DynamicArray& other) {
        for (int i = 0; i < count; ++i) {
            if (i < other.count) {
                data[i] += other.data[i];
            }
        }
    }

    void sub(const DynamicArray& other) {
        for (int i = 0; i < count; ++i) {
            if (i < other.count) {
                data[i] -= other.data[i];
            }
        }
    }

    double distance(const DynamicArray& other) const {
        if (count != other.count) {
            throw invalid_argument("Размеры массивов должны совпадать");
        }

        if constexpr (is_arithmetic_v<T>) {
            double sum = 0;
            for (int i = 0; i < count; ++i) {
                double difference = data[i] - other.data[i];
                sum += difference * difference;
            }
            return sqrt(sum);
        } else {
            throw bad_typeid();
        }
    }

    void print() const {
        for (int i = 0; i < count; ++i) {
            cout << data[i] << ' ';
        }
        cout << '\n';
    }
};

template <typename T>
ostream& operator<<(ostream& output, const DynamicArray<T>& array) {
    for (int i = 0; i < array.size(); ++i) {
        output << array.get(i) << ' ';
    }
    return output;
}
