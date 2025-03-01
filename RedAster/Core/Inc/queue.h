/*
 * queue.h
 *
 *  Created on: Feb 12, 2025
 *      Aut*-+hor: Lorenzo
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Queue {
private:
    std::vector<T> data;        // Queue with std::vector

public:
    Queue();
    ~Queue();

    void enqueue(const T& value);
    T dequeue();                // dequeue and return the element (FIFO)
    T front() const;            // return front element
    bool isEmpty() const;       // check if the queue is empty
    size_t getSize() const;

};

#include "queue.cpp"

#endif /* INC_QUEUE_H_ */
