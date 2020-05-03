#pragma once
#include <type_traits>
#include <string>

template <typename _Ty>
class ListNode {
private:
	_Ty value_;
	ListNode<_Ty>* next_;

public:
	ListNode() : value_(_Ty()), next_(nullptr) {}
	ListNode(_Ty value, ListNode<_Ty>* next = nullptr) : value_(value), next_(next) {}
	ListNode(const ListNode<_Ty>& ln) {
		static_assert(std::is_copy_constructible<_Ty>::value, 
			"Cannot copy because type is not copy constructible");
		value_ = ln.value_;
		*next_ = *(ln.next_);
	}
	~ListNode() {}
	ListNode<_Ty>& operator = (ListNode<_Ty>& ln) {
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
	ListNode<_Ty>* next() const { return next_; }

	// setter for next
	void next(ListNode<_Ty>* next__) {
		next_ = next__;
	}
};