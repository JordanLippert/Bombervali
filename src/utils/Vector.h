//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_VECTOR_H
#define GAME02_CBP_VECTOR_H

#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data;        // Ponteiro para o array dinâmico.
    int capacity {}; // Capacidade máxima do array.
    int size {};     // Número atual de elementos no array.

public:
    // Construtor padrão: Inicializa os membros.
    Vector() : data(nullptr), capacity(0), size(0) {}

    // Destrutor: Libera a memória alocada para o array.
    ~Vector() {
        delete[] data;
    }

    // Adiciona um elemento ao final do vetor.
    void push(const T& value) {
        if (size == capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                if (capacity == 1) capacity = 5;
                capacity *= 2;
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

    // Remove um elemento no índice especificado.
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

    // Limpa o vetor, liberando a memória e redefinindo os membros.
    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
    }

    // Retorna uma referência ao elemento no índice especificado.
    T& get(int index) {
        return (*this)[index];
    }

    // Sobrecarga do operador [] para acesso aos elementos por índice.
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Retorna o tamanho atual do vetor.
    int getSize() const {
        return size;
    }

    // Verifica se o vetor está vazio.
    bool isEmpty() const {
        return size == 0;
    }
};


#endif //GAME02_CBP_VECTOR_H
