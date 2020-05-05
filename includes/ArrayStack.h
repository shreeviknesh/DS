#pragma once
#include <stdexcept>
#include <cstdint>

// Array implementation of stack 
template <typename Type, size_t MaxSize>
class ArrayStack {
private:
	size_t m_top;
	Type m_data[MaxSize];

public:
	ArrayStack();
	ArrayStack(const ArrayStack<Type, MaxSize>& as);
	ArrayStack<Type, MaxSize>& operator =(const ArrayStack<Type, MaxSize>& as);
	~ArrayStack();

	// Insert a value as top
	void push(const Type value);

	// Remove the top value
	void pop();
	
	// Return the top value
	Type peek() const { return m_data[m_top]; }

	// Get the MaxSize of the ArrayStack
	size_t size() const { return MaxSize; }
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
void ArrayStack<Type, MaxSize>::pop() {
	if (m_top < 0) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot pop: ArrayStack is empty");
		#endif
		return;
	}
	m_top--;
}