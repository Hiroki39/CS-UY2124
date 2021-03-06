/*
  Vector Class
  Demonstrates:
    Good example of copy control
    Dynamic arrays and pointer arithmetic
    Square bracket operator
    Implementation of an important data structure
*/
#include <iostream>
using namespace std;

class Vector {
public:
    class Iterator {
        // non-member
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.valPtr != rhs.valPtr;
        }

    public:
        Iterator(int* p) : valPtr(p) {}
        Iterator& operator++() {  // ++iter
            valPtr++;
            return *this;
        }
        // dereference operator
        int& operator*() { return *valPtr; }

    private:
        int* valPtr;
    };

    class Const_Iterator {
        // non-member
        friend bool operator!=(const Const_Iterator& lhs,
                               const Const_Iterator& rhs) {
            return lhs.valPtr != rhs.valPtr;
        }

    public:
        Const_Iterator(int* p) : valPtr(p) {}
        Const_Iterator& operator++() {  // ++iter
            valPtr++;
            return *this;
        }
        // dereference operator
        const int& operator*() { return *valPtr; }

    private:
        int* valPtr;
    };

    Vector() : theSize(0), theCapacity(8), data(new int[theCapacity]) {}
    // Vector(size_t size, int value = 0) {}
    ~Vector() {
        // delete data; this will only delete one integer!
        // data is actually a pointer to int
        delete[] data;
    }

    explicit Vector(size_t size, int value = 0)
        : theSize(size), theCapacity(size), data(new int[theCapacity]) {
        for (size_t i = 0; i < theSize; i++) {
            data[i] = value;
        }
    }

    Vector(const Vector& rhs)
        : theSize(rhs.theSize),
          theCapacity(rhs.theCapacity),
          data(new int[rhs.theCapacity]) {
        for (size_t i = 0; i < theSize; i++) {
            data[i] = rhs.data[i];
        }
    }

    Vector& operator=(const Vector& rhs) {
        // Self assignment
        if (&rhs != this) {
            // free up our resources
            delete[] data;
            // allocate new resources
            data = new int[rhs.theCapacity];
            // copy over any information
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            for (size_t i = 0; i < theSize; i++) {
                data[i] = rhs.data[i];
            }
        }
        return *this;
    }

    void push_back(int val) {
        if (theSize == theCapacity) {  // no more free space
            int* oldData = data;       // remember where the old data is
            data = new int[2 * theCapacity];
            for (size_t i = 0; i < theCapacity; i++) {
                data[i] = oldData[i];
            }
            delete[] oldData;
            theCapacity *= 2;
        }
        data[theSize] = val;
        theSize++;
    }

    size_t size() const { return theSize; }
    void clear() { theSize = 0; }
    void pop_back() { theSize--; }
    // Operator overload for square brackets (v[index])
    int operator[](size_t index) const { return data[index]; }
    // v[index] = val;
    int& operator[](size_t index) { return data[index]; }  // reference return

    // overload begin() and end() with const and non-const version

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + theSize); }

    Const_Iterator begin() const { return Const_Iterator(data); }
    Const_Iterator end() const { return Const_Iterator(data + theSize); }

private:
    size_t theSize;  // C++ does not allow to have field & method with same name
    size_t theCapacity;
    int* data;
};

void printVec(const Vector& v) {
    cout << "[ ";
    for (int val : v) {  // to make this ranged-for loop possible we need
                         // begin() and end() method
        cout << val << " ";
    }
    cout << "]" << endl;
}

int main() {
    Vector v;  // not templated. Our vector can only hold ints.
    v.push_back(17);
    v.push_back(42);
    v.push_back(6);
    v.push_back(28);
    Vector a = v;

    printVec(v);

    // v = 17;
    // the compiler would interpret it as Vector(17), but we need to make
    // it reporting an error!

    v[0] = 100;

    Vector v2 = v;

    for (int val : v2) {
        cout << val << ' ';
    }
    cout << endl;
    // equivalent to
    for (Vector::Iterator iter = v2.begin(); iter != v2.end(); ++iter) {
        int temp = *iter;
        cout << temp << ' ';
    }
    cout << endl;

    for (int& val : v2) {
        val += 2;
    }
    // equivalent to
    for (Vector::Iterator iter = v2.begin(); iter != v2.end(); ++iter) {
        *iter += 2;
    }
}
