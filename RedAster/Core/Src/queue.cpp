/*
 * queue.cpp
 *
 *  Created on: Feb 12, 2025
 *      Author: Lorenzo
 */

#include <queue.h>

template <typename T>
void Queue<T>::enqueue(const T& value) {
    this->data.push_back(value);
}

template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty, cannot dequeue.\n");
    }
    T frontElement = this->data.front();
    this->data.erase(this->data.begin());
    return frontElement;
}

template <typename T>
T Queue<T>::front() const {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty, cannot peek.");
    }
    return this->data.front();
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return this->data.empty();
}

template <typename T>
size_t Queue<T>::getSize() const {
    return this->data.size();
}


