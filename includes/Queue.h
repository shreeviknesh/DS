/*
 * This file is part of the DS Library (https://github.com/shreeviknesh/DS).
 *
 * MIT License
 *
 * Copyright (c) 2020 Shreeviknesh
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include <initializer_list>

template<typename Type>
class Queue
{
  public:
    class Node;

    Queue() : m_front(nullptr), m_rear(nullptr), m_size(0) {}
    Queue(const Queue<Type> &queue) : m_front(queue.m_front), m_rear(queue.m_rear), m_size(queue.m_size) {}
    Queue(std::initializer_list<Type> values);
    ~Queue();

    /* Get the first element */
    inline Type front() const { return m_front->value; }

    /* Get the last element*/
    inline Type back() const { return m_rear->value; }

    /* Check if queue is empty */
    inline bool empty() const { return (m_size == 0); }

    /* Get the size of the queue */
    inline size_t size() const { return m_size; }

    /* Insert an element to the end of the queue */
    void push(const Type value);

    /* Remove the first element of the queue*/
    Type pop();

    /* Delete all elements of the queue */
    void clear();

  private:
    Node *m_front;
    Node *m_rear;
    size_t m_size;
};

template<typename Type>
class Queue<Type>::Node
{
    Type value;
    Node *next;
    Node *prev;

    Node() : value(Type()), next(nullptr), prev(nullptr) {}
    Node(Type value_, Node *next_ = nullptr, Node *prev_ = nullptr) : value(value_), next(next_), prev(prev_) {}

    friend class Queue<Type>;
};

template<typename Type>
Queue<Type>::Queue(std::initializer_list<Type> values) {
    m_size = 0;
    m_front = nullptr;
    m_rear = nullptr;
    if (values.size() == 0) {
        m_front = nullptr;
        m_rear = nullptr;
        m_size = 0;
    }
    else {
        for (Type val : values) {
            push(val);
        }
    }
}

template<typename Type>
Queue<Type>::~Queue() {
    clear();
}

template<typename Type>
void Queue<Type>::push(const Type value) {
    if (m_front == nullptr) {
        Node *newNode = new Node(value);
        m_front = newNode;
        m_rear = newNode;
        m_size = 1;
    }
    else {
        Node *newNode = new Node(value, nullptr, m_rear);
        m_rear->next = newNode;
        m_rear = newNode;
        m_size++;
    }
}

template<typename Type>
Type Queue<Type>::pop() {
    if (m_size == 0) {
        return Type();
    }
    else if (m_size == 1) {
        Node *toDelete = m_front;
        m_front = nullptr;
        m_rear = nullptr;
        m_size = 0;
        Type val = toDelete->value;
        delete toDelete;
        return val;
    }
    else {
        Node *toDelete = m_front;
        Type val = m_front->value;
        m_front = m_front->next;
        m_size--;
        delete toDelete;
        return val;
    }
}

template<typename Type>
void Queue<Type>::clear() {
    while (m_size > 0) {
        pop();
    }
}

#endif
