/*
 * queue.cpp
 *
 *  Created on: Feb 12, 2025
 *      Author: Lorenzo
 */

#include <queue.h>

template <typename T>
Queue<T>::Queue()
    : capacity(100), front(0), rear(-1), size(0) {
    this->data = new T[this->capacity];
}

template <typename T>
Queue<T>::~Queue() {
    delete[] this->data;
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
    if (this->size == this->capacity) {
        resize();
    }
    this->rear = (this->rear + 1) % this->capacity;  // Movimento circolare nell'array
    this->data[this->rear] = value;
    ++this->size;
}

template <typename T>
void Queue<T>::dequeue() {
    if (isEmpty()) {
        std::cerr << "Queue is empty, cannot dequeue.\n";
        return;
    }
    this->front = (this->front + 1) % this->capacity;  // Movimento circolare nell'array
    --this->size;
}

template <typename T>
T Queue<T>::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty, cannot peek.");
    }
    return this->data[this->front];
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return this->size == 0;
}

template <typename T>
int Queue<T>::getSize() const {
    return this->size;
}

template <typename T>
void Queue<T>::printQueue() const {
    if (isEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }
    std::cout << "Queue elements: ";
    for (int i = 0; i < this->size; ++i) {
        std::cout << this->data[(this->front + i) % this->capacity] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Queue<T>::resize() {
    int newCapacity = this->capacity * 2;
    T* newData = new T[newCapacity];

    for (int i = 0; i < this->size; ++i) {
        newData[i] = this->data[(this->front + i) % this->capacity];
    }

    delete[] this->data;
    this->data = newData;
    this->front = 0;
    this->rear = size - 1;
    this->capacity = newCapacity;
}

