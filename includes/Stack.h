#pragma once
#include "utils\Node.h"
#include <stdexcept>

// Linked-list implementation of stack
template <typename Type>
class Stack {
private:
	Node<Type>* m_top;

public:
	Stack() : m_top(nullptr) {}

	Stack(Node<Type>* top) : m_top(top) {}

	Stack(const Stack<Type>& s) {
		if (s.m_top == nullptr) {
			m_top = nullptr;
		}
		else {
			*m_top = *(s.m_top);
		}
	}

	Stack<Type>& operator = (const Stack<Type>& s) {
		if (s.m_top == nullptr) {
			m_top = nullptr;
		}
		else {
			*m_top = *(s.m_top);
		}
		return *this;
	}

	~Stack() {
		while (m_top != nullptr) {
			pop();
		}
	}

	// Check if the stack is empty?
	bool isEmpty() const { return (m_top == nullptr); }

	// Insert a value as top
	void push(const Type value) {
		m_top = new Node<Type>(value, m_top);
	}

	// Pop the top value
	Type pop() {
		if (m_top == nullptr) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot pop: Stack is empty");
			#endif
			return Type();
		}

		Node<Type>* temp = m_top;
		Type value = m_top->value;
		m_top = m_top->next;
		delete temp;
		return value;
	}

	// Get the top value
	Type peek() const {
		if (m_top == nullptr) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot peek: Stack is empty");
			#endif
			return Type();
		}

		return m_top->value;
	}

	// Clear the stack
	void clear() {
		while (!isEmpty()) {
			pop();
		}
	}
};