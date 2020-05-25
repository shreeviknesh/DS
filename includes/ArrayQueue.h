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

#ifndef DS_ARRAY_QUEUE_H
#define DS_ARRAY_QUEUE_H

#include <stdexcept>

template<typename Type, size_t MaxSize = 32>
class ArrayQueue {
public:
    ArrayQueue() : m_back(-1) {}
    ArrayQueue(const ArrayQueue<Type, MaxSize>& queue);
    ~ArrayQueue() { clear(); }

    inline bool empty() const { return (m_back == -1); }
    inline size_t size() const { return (m_back + 1); }
       
    inline Type front() const { return m_data[0]; }
    inline Type back() const { return m_data[m_back]; }

    void push(Type value);
    Type pop();
    void clear() { m_back = -1; }

private:
    Type m_data[MaxSize];
    size_t m_back;
};

template<typename Type, size_t MaxSize>
ArrayQueue<Type, MaxSize>::ArrayQueue(const ArrayQueue<Type, MaxSize>& queue) {
    for (size_t i = 0; i <= queue.m_back; i++) {
        m_data[i] = queue.m_data[i];
    }
    m_back = queue.m_back;
}

template<typename Type, size_t MaxSize>
void ArrayQueue<Type, MaxSize>::push(Type value) {
    if (m_back == MaxSize - 1) {
        #ifdef _DEBUG
        throw std::out_of_range("Queue is full.");
        #endif // _DEBUG
        return;
    }
    m_data[++m_back] = value;
}

template<typename Type, size_t MaxSize>
Type ArrayQueue<Type, MaxSize>::pop() {
    if (m_back == -1) {
        return Type();
    }
    Type returnValue = m_data[0];
    for (size_t i = 0; i < m_back; i++) {
        m_data[i] = m_data[i + 1];
    }
    m_back--;
    return returnValue;
}

#endif
