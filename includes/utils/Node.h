#pragma once
#include <type_traits>
#include <string>

template <typename _Ty>
class Node {
private:
	_Ty value_;
	Node<_Ty>* next_;

public:
	Node() : value_(_Ty()), next_(nullptr) {}
	Node(_Ty value, Node<_Ty>* next = nullptr) : value_(value), next_(next) {}
	Node(const Node<_Ty>& ln) {
		static_assert(std::is_copy_constructible<_Ty>::value, 
			"Cannot copy because type is not copy constructible");
		value_ = ln.value_;
		*next_ = *(ln.next_);
	}
	~Node() {}
	Node<_Ty>& operator = (Node<_Ty>& ln) {
		value_ = ln.value_;
		*next_ = *(ln.next_);
		return *this;
	}

	// getter for value
	_Ty value() const { return value_; }

	// setter for value
	void value(_Ty value__) {
		value_ = value__;
	}

	// getter for next
	Node<_Ty>* next() const { return next_; }

	// setter for next
	void next(Node<_Ty>* next__) {
		next_ = next__;
	}
};