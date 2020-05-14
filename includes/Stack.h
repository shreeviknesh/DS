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

// Implementation of Stack
template <typename Type>
class Stack {
public:
	class Node;

	Stack() : m_top(nullptr) {}
	Stack(Node* top) : m_top(top) {}
	Stack(const Stack<Type>& s);
	~Stack() { clear(); }

	Stack<Type>& operator = (const Stack<Type>& s);

	// Check if the stack is empty
	inline bool empty() const { return (m_top == nullptr); }

	// Push a value to the top of the Stack
	void push(const Type value);

	// Pop the top value of the Stack
	Type pop();

	// Get the top value of the Stack
	Type peek() const;

	// Clear all the elements of the Stack
	void clear();

private:
	Node* m_top;
};

template <typename Type>
class Stack<Type>::Node {
	Type value;
	Node* next;

	Node() 
		: value(Type()), next(nullptr) {}

	Node(Type value_, Node* next_ = nullptr) 
		: value(value_), next(next_) {}

	friend class Stack<Type>;
};

template <typename Type>
Stack<Type>::Stack(const Stack<Type>& s) {
	if (s.m_top == nullptr) {
		m_top = nullptr;
	}
	else {
		*m_top = *(s.m_top);
	}
}

template <typename Type>
Stack<Type>& Stack<Type>::operator = (const Stack<Type>& s) {
	Stack(s);
	return *this;
}

template <typename Type>
void Stack<Type>::push(const Type value) {
	m_top = new Node(value, m_top);
}

template <typename Type>
Type Stack<Type>::pop() {
	if (m_top == nullptr) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot pop: Stack is empty");
		#endif
		return Type();
	}
	Node* temp = m_top;
	Type value = m_top->value;
	m_top = m_top->next;
	delete temp;
	return value;
}

template <typename Type>
Type Stack<Type>::peek() const {
	if (m_top == nullptr) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot peek: Stack is empty");
		#endif
		return Type();
	}
	return m_top->value;
}

template<typename Type>
void Stack<Type>::clear() {
	while (m_top != nullptr) {
		pop();
	}
}
