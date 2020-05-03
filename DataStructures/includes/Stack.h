#pragma once
#include "utils\ListNode.h"
#include <stdexcept>

// Linked-list implementation of stack
template <typename _Ty>
class Stack {
private:
	ListNode<_Ty>* top_;

public:
	Stack() : top_(nullptr) {}
	Stack(ListNode<_Ty>* top) : top_(top) {}
	Stack(const Stack<_Ty>& s) : top_(s.top_) {}
	~Stack() {
		while (top_ != nullptr) {
			pop();
		}
	}

	// Insert a value as top
	void push(const _Ty value) {
		ListNode<_Ty>* temp = top_;
		top_ = new ListNode<_Ty>(value, temp);
	}

	// Pop the top value
	_Ty pop() {
		if (top_ == nullptr) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot pop: Stack is empty");
			#endif
				return _Ty();
		}
		ListNode<_Ty>* temp = top_;
		top_ = top_->next();
		temp->next(nullptr);
		return temp->value();
	}

	// Get the top value
	_Ty peek() const {
		if (top_ == nullptr) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot peek: Stack is empty");
			#endif
			return _Ty();
		}
		return top_->value();
	}
};