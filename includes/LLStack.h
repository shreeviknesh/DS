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

#ifndef DS_LL_STACK_H
#define DS_LL_STACK_H

#include "LinkedList.h"

// LinkedList Implementation of Stack
template<typename Type>
class LLStack
{
  public:
    LLStack() { m_list.clear(); }
    LLStack(const LLStack<Type> &lls) : m_list(lls.m_list) {}
    ~LLStack() { clear(); }

    inline bool empty() const { return m_list.empty(); }
    void push(const Type value) { m_list.unshift(value); }
    Type pop();
    Type peek() const { return m_list.get(0); }
    void clear() { m_list.clear(); }

  private:
    LinkedList<Type> m_list;
};

template<typename Type>
Type LLStack<Type>::pop() {
    if (empty()) {
        return Type();
    }
    else {
        Type temp = m_list.get(0);
        m_list.remove();
        return temp;
    }
}

#endif
