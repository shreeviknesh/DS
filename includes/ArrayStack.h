#pragma once
#include <stdexcept>
#include <cstdint>

typedef size_t index;

// Array implementation of stack 
template <typename Type, index MaxSize>
class ArrayStack {
private:
	index m_top;
	Type m_data[MaxSize];

public:
	ArrayStack() : m_top(-1) {
		static_assert(MaxSize > 0, "ArrayStack MaxSize has to be positive non-zero integer");
	}

	ArrayStack(index top, Type data[MaxSize]) = delete;

	ArrayStack(const ArrayStack<Type, MaxSize>& as) {
		if (as.m_top > MaxSize) {
			#ifdef _DEBUG
				throw std::out_of_range("Top cannot be greater than MaxSize");
			#endif
			ArrayStack();
		}
		m_top = as.m_top;
		for (index i = 0; i <= as.m_top; i++) {
			m_data[i] = as.m_data[i];
		}
	}

	ArrayStack<Type, MaxSize>& operator =(const ArrayStack<Type, MaxSize>& as) {
		m_top = as.m_top;
		for (index i = 0; i <= as.m_top; i++) {
			m_data[i] = as.m_data[i];
		}
		return *this;
	}

	~ArrayStack() { 
		while (m_top > 0) {
			pop();
		}
	}

	// Insert a value as top
	void push(const Type value) {
		if (m_top == MaxSize - 1) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot push: ArrayStack MaxSize exceeded");
			#endif
			return;
		}
		m_data[++m_top] = value;
	}

	// Remove the top value
	void pop() {
		if (m_top < 0) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot pop: ArrayStack is empty");
			#endif
			return;
		}
		m_top--;
	}
	
	// Return the top value
	Type peek() const {
		if (m_top < 0) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot peek: ArrayStack is empty");
			#endif
			return Type();
		}
		return m_data[m_top];
	}

	// Get the MaxSize of the ArrayStack
	index size() const {
		return MaxSize;
	}
};