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

#pragma once
#include <stdexcept>
#include <cstdint>

// Array implementation of Stack 
template <typename Type, size_t MaxSize = 32>
class ArrayStack {
private:
	size_t m_top;
	Type m_data[MaxSize];

public:
	ArrayStack();
	ArrayStack(const ArrayStack<Type, MaxSize>& as);
	ArrayStack<Type, MaxSize>& operator =(const ArrayStack<Type, MaxSize>& as);
	~ArrayStack();

	// Check if the stack is empty
	inline bool empty() const { return (m_top == -1); }

	// Push a value to the top of the ArrayStack
	void push(const Type value);

	// Pop the top value of the ArrayStack
	Type pop();
	
	// Get the top value of the ArrayStack
	inline Type peek() const { return m_data[m_top]; }

	// Get the MaxSize of the ArrayStack
	inline size_t size() const { return MaxSize; }
};

template <typename Type, size_t MaxSize>
ArrayStack<Type, MaxSize>::ArrayStack() : m_top(-1) {
	static_assert(MaxSize > 0, "ArrayStack MaxSize has to be positive non-zero integer");
}

template <typename Type, size_t MaxSize>
ArrayStack<Type, MaxSize>::ArrayStack(const ArrayStack<Type, MaxSize>& as) {
	if (as.m_top > MaxSize) {
		#ifdef _DEBUG
			throw std::out_of_range("Top cannot be greater than MaxSize");
		#endif
		ArrayStack();
	}
	m_top = as.m_top;
	for (size_t i = 0; i <= as.m_top; i++) {
		m_data[i] = as.m_data[i];
	}
}


template <typename Type, size_t MaxSize>
ArrayStack<Type, MaxSize>& ArrayStack<Type, MaxSize>::operator =(const ArrayStack<Type, MaxSize>& as) {
	m_top = as.m_top;
	for (size_t i = 0; i <= as.m_top; i++) {
		m_data[i] = as.m_data[i];
	}
	return *this;
}

template <typename Type, size_t MaxSize>
ArrayStack<Type, MaxSize>::~ArrayStack() {
	while (m_top > 0) {
		pop();
	}
}

template <typename Type, size_t MaxSize>
void ArrayStack<Type, MaxSize>::push(const Type value) {
	if (m_top == MaxSize - 1) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot push: ArrayStack MaxSize exceeded");
		#endif
		return;
	}
	m_data[++m_top] = value;
}

template <typename Type, size_t MaxSize>
Type ArrayStack<Type, MaxSize>::pop() {
	if (m_top < 0) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot pop: ArrayStack is empty");
		#endif
		return Type();
	}
	m_top--;
	return m_data[m_top + 1];
}
