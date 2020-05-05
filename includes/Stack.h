#pragma once
#include <stdexcept>

// Linked-list implementation of stack
template <typename Type>
class Stack {
public:
	class Node;

	Stack() : m_top(nullptr) {}
	Stack(Node* top) : m_top(top) {}
	Stack(const Stack<Type>& s);
	~Stack();

	// Copy assignment operator
	Stack<Type>& operator = (const Stack<Type>& s);

	// Check if the stack is empty
	bool isEmpty() const { return (m_top == nullptr); }

	// Insert a value as top
	void push(const Type value);

	// Pop the top value
	Type pop();

	// Get the top value
	Type peek() const;

	// Clear the stack
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
Stack<Type>::~Stack() {
	while (m_top != nullptr) {
		pop();
	}
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

template <typename Type>
void Stack<Type>::clear() {
	~Stack();
}