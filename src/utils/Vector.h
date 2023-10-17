//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_VECTOR_H
#define GAME02_CBP_VECTOR_H

#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data;
    int capacity {};
    int size {};

public:
    Vector() : data(nullptr), capacity(0), size(0) {}
    Vector(int initialCapacity) {
        T* newData = new T[initialCapacity];

        this->capacity = initialCapacity;
        this->size = 0;
        this->data = newData;
    }

    ~Vector() {
        delete[] data;
    }

    void push(const T& value) {
        if (size == capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity += 2;
            }

            T* newData = new T[capacity];

            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
        }

        data[size++] = value;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }

        size--;

        if (size < capacity / 2) {
            capacity /= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
    }

    void pop() {
        if (size > 0) {
            size--;
        }
    }

    T& get(int index) {
        return this[index];
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};


#endif //GAME02_CBP_VECTOR_H
