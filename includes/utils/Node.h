#pragma once
#include <type_traits>
#include <string>

template <typename Type>
class Node {
public:
	Type value;
	Node<Type>* next;

	Node() : value(Type()), next(nullptr) {}

	Node(Type _value, Node<Type>* _next = nullptr) : value(_value), next(_next) {}

	Node(const Node<Type>& ln) {
		value = ln.value;
		if (ln.next == nullptr) {
			next = nullptr;
		}
		else {
			*next = *(ln.next);
		}
	}

	Node<Type>& operator = (const Node<Type>& ln) {
		value = ln.value;
		if (ln.next == nullptr) {
			next = nullptr;
		}
		else {
			*next = *(ln.next);
		}
		return *this;
	}
};