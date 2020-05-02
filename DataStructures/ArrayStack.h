#pragma once

#ifdef _DEBUG
#define DS_DEBUG
#endif

#include <cstdint>
#include <stdexcept>

namespace DS {
	template <typename _Ty, size_t _MAX_SIZE>
	class ArrayStack {
	private:
		std::uint16_t top_;
		_Ty data_[_MAX_SIZE];

	public:
		ArrayStack() : top_(-1) {
			static_assert(_MAX_SIZE > 0, "ArrayStack MAX_SIZE has to be positive non-zero integer");
		}
		ArrayStack(ArrayStack& as) = delete;

		void push(const _Ty value) {
			if (top_ == _MAX_SIZE - 1) {
				#ifdef DS_DEBUG
					throw std::out_of_range("Cannot push: ArrayStack MAX_SIZE exceeded");
				#endif
				return;
			}
			data_[++top_] = value;
		}

		_Ty pop() {
			if (top_ < 0) {
				#ifdef DS_DEBUG
					throw std::out_of_range("Cannot pop: ArrayStack is empty");
				#endif
				return;
			}
			return data_[top_--];
		}

		_Ty peek() {
			if (top_ < 0) {
				#ifdef DS_DEBUG
					throw std::out_of_range("Cannot peek: ArrayStack is empty");
				#endif
			}
			return data_[top_];
		}

		std::uint16_t top() {
			return top_;
		}

		size_t size() {
			return _MAX_SIZE;
		}
	};
}