#pragma once
#include <cstdint>
#include <stdexcept>

// Array implementation of stack 
template <typename _Ty, size_t _MAX_SIZE>
class ArrayStack {
private:
	std::uint16_t top_;
	_Ty data_[_MAX_SIZE];

public:
	ArrayStack() : top_(-1) {
		static_assert(_MAX_SIZE > 0, "ArrayStack MAX_SIZE has to be positive non-zero integer");
	}
	ArrayStack(std::uint16_t top, _Ty data[_MAX_SIZE]) : top_(top) {
		static_assert(top < _MAX_SIZE, "ArrayStack top cannot be greater than MAX_SIZE");
		for (std::uint16_t i = 0; i <= top; i++) {
			data_[i] = data[i];
		}
	}
	ArrayStack(const ArrayStack<_Ty, _MAX_SIZE>& as) : top_(as.top_) {
		static_assert(as.top_ < _MAX_SIZE, "ArrayStack top cannot be greater than MAX_SIZE");
		for (std::uint16_t i = 0; i <= as.top_; i++) {
			data_[i] = as.data_[i];
		}
	}
	~ArrayStack() {
		while (top_ >= 0) {
			pop();
		}
	}

	// Insert a value as top
	void push(const _Ty value) {
		if (top_ == _MAX_SIZE - 1) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot push: ArrayStack MAX_SIZE exceeded");
			#endif
			return;
		}
		data_[++top_] = value;
	}

	// Pop the top value
	_Ty pop() {
		if (top_ < 0) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot pop: ArrayStack is empty");
			#endif
			return _Ty();
		}
		return data_[top_--];
	}
	
	// Get the top value
	_Ty peek() const {
		if (top_ < 0) {
			#ifdef _DEBUG
				throw std::out_of_range("Cannot peek: ArrayStack is empty");
			#endif
			return _Ty();
		}
		return data_[top_];
	}

	// Get the MAX_SIZE of the ArrayStack
	size_t size() const {
		return _MAX_SIZE;
	}
};

