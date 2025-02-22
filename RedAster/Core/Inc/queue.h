/*
 * queue.h
 *
 *  Created on: Feb 12, 2025
 *      Aut*-+hor: Lorenzo
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <iostream>

template <typename T>
class Queue {
private:
    T* data;        // Array dinamico per memorizzare gli elementi della coda
    int front;      // Indice dell'elemento in testa alla coda
    int rear;       // Indice dell'ultimo elemento nella coda
    int capacity;   // Capacità massima dell'array
    int size;       // Numero di elementi attualmente nella coda

    void resize();  // Metodo privato per ridimensionare l'array quando è pieno

public:
    Queue();
    ~Queue();

    void enqueue(const T& value);
    void dequeue();
    T peek() const;
    bool isEmpty() const;
    int getSize() const;
    void printQueue() const;
};

#include "queue.cpp"  // Inclusione del file .cpp per evitare problemi con i template

#endif /* INC_QUEUE_H_ */
