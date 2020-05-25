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

#ifndef DS_DEQUE_H
#define DS_DEQUE_H

#include <initializer_list>
#include <stdexcept>
#include "DoublyLinkedList.h"

template <typename Type>
class Deque {
public:
    Deque() { m_list.clear(); }
    Deque(Type values[], size_t size) : m_list(values, size) {}
    Deque(std::initializer_list<Type> values): m_list(values) {}
    ~Deque() { m_list.clear(); }

    inline Type front() const { return m_list.getHead(); }
    inline Type back() const { return m_list.getTail(); }
    inline bool empty() const { return m_list.empty(); }
    
    void push_back(const Type value) { m_list.insert(value); }
    void push_front(const Type value) { m_list.unshift(value); }
    Type pop_back();
    Type pop_front();
    void clear() { m_list.clear(); }

private:
    DoublyLinkedList<Type> m_list;
};

template<typename Type>
inline Type Deque<Type>::pop_back() {
    if (empty()) {
        #ifdef _DEBUG
        throw std::out_of_range("Deque is empty");
        #endif // _DEBUG
        return Type();
    }
    Type value = m_list.getTail();
    m_list.removeTail();
    return value;
}

template<typename Type>
Type Deque<Type>::pop_front() {
    if (empty()) {
        #ifdef _DEBUG
        throw std::out_of_range("Deque is empty");
        #endif // _DEBUG
        return Type();
    }
    Type value = m_list.getHead();
    m_list.removeHead();
    return value;
}

#endif
