#include "DynamicArray.h"
int main() {
    DynamicArray a(2); a.set(0, 10); a.set(1, 20);
    DynamicArray b(a); b.pushBack(30); a.add(b); a.sub(b); a.print();
}
