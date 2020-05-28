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

#ifndef DS_LL_QUEUE_H
#define DS_LL_QUEUE_H

#include "DoublyLinkedList.h"

template<typename Type>
class LLQueue
{
  public:
    LLQueue() { m_list.clear(); }
    LLQueue(const LLQueue<Type> &llq) = delete;
    ~LLQueue() { clear(); }

    inline Type front() const { return m_list.getHead(); }
    inline Type back() const { return m_list.getTail(); }
    inline bool empty() const { return m_list.empty(); }

    void push(const Type value) { m_list.insert(value); }
    Type pop();
    void clear() { m_list.clear(); }

  private:
    DoublyLinkedList<Type> m_list;
};

template<typename Type>
Type LLQueue<Type>::pop() {
    if (empty()) {
#ifdef _DEBUG
        throw std::out_of_range("LLQueue is empty.");
#endif// _DEBUG
        return Type();
    }
    Type returnValue = m_list.getHead();
    m_list.removeHead();
    return returnValue;
}

#endif
