#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <iostream>

class DynamicArray {
    int* data;
    int count;
public:
    explicit DynamicArray(int size) : data(new int[size]{}), count(size) {}
    ~DynamicArray() { delete[] data; }
    DynamicArray(const DynamicArray& other) : data(new int[other.count]), count(other.count) {
        for (int i = 0; i < count; ++i) data[i] = other.data[i];
    }
    int size() const { return count; }
    int get(int i) const {
        if (i < 0 || i >= count) throw "index";
        return data[i];
    }
    void set(int i, int value) {
        if (i < 0 || i >= count) throw "index";
        if (value < -100 || value > 100) throw "value";
        data[i] = value;
    }
    void pushBack(int value) {
        if (value < -100 || value > 100) throw "value";
        int* bigger = new int[count + 1];
        for (int i = 0; i < count; ++i) bigger[i] = data[i];
        bigger[count] = value;
        delete[] data;
        data = bigger;
        ++count;
    }
    void add(const DynamicArray& other) {
        for (int i = 0; i < count; ++i) data[i] += i < other.count ? other.data[i] : 0;
    }
    void sub(const DynamicArray& other) {
        for (int i = 0; i < count; ++i) data[i] -= i < other.count ? other.data[i] : 0;
    }
    void print() const {
        for (int i = 0; i < count; ++i) std::cout << data[i] << ' ';
        std::cout << '\n';
    }
};
#endif
