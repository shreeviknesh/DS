#pragma once
#include <type_traits>
#include <string>

template <typename Type>
class Node {
private:
	Type m_value;
	Node<Type>* m_next;

public:
	Node() : m_value(Type()), m_next(nullptr) {}

	Node(Type value, Node<Type>* next = nullptr) : m_value(value), m_next(next) {}

	Node(const Node<Type>& ln) {
		static_assert(std::is_copy_constructible<Type>::value,
			"Cannot copy because type is not copy constructible");

		m_value = ln.m_value;
		if (ln.m_next == nullptr) {
			m_next = nullptr;
		}
		else {
			*m_next = *(ln.m_next);
		}
	}

	Node<Type>& operator = (const Node<Type>& ln) {
		static_assert(std::is_copy_constructible<Type>::value,
			"Cannot copy because type is not copy constructible");

		m_value = ln.m_value;
		if (ln.m_next == nullptr) {
			m_next = nullptr;
		}
		else {
			*m_next = *(ln.m_next);
		}
		return *this;
	}

	~Node() {}

	// getter for value
	Type value() const { return m_value; }

	// setter for value
	void value(Type value__) {
		m_value = value__;
	}

	// getter for next
	Node<Type>* next() const { return m_next; }

	// setter for next
	void next(Node<Type>* next__) {
		m_next = next__;
	}
};