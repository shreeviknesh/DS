/*
 * This file is part of the DS Library (https://github.com/shreeviknesh/DS).
 *
 * MIT License
 *
 * Copyright (c) 2020 Shreeviknesh
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef DS_LINKED_LIST_H
#define DS_LINKED_LIST_H

#include <initializer_list>
#include <stdexcept>

// Implementation of LinkedList
template <typename Type>
class LinkedList {
public:
	class Node;

	LinkedList() : m_head(nullptr) {}
	LinkedList(Node* head);
	LinkedList(Type* values, size_t size);
	LinkedList(std::initializer_list<Type> values);
	LinkedList(const LinkedList<Type>& ll);
	~LinkedList() { clear(); }

	size_t size() const;
	inline bool empty() const { return (m_head == nullptr); }

	// Insert an element at the beginning
	void unshift(Type value);

	// Insert an element at the end
	void insert(Type value);

	// Insert an element at pos
	void insert(size_t pos, Type value);

	// Remove the first element
	bool remove();

	// Remove the first element with value as val
	bool remove(Type value);

	// Clear all the elements of the LinkedList
	void clear();

	// Get the element at pos
	Type& get(size_t pos) const;
	Type& operator [](size_t pos) const { return get(pos); }

	// Reverse the LinkedList
	void reverse();

private:
	Node* m_head;
};

template<typename Type>
class LinkedList<Type>::Node {
public:
	Type value;
	Node* next;

	Node() 
		: value(Type()), next(nullptr) {}

	Node(Type value_, Node* next_ = nullptr) 
		: value(value_), next(next_) {}
};

template<typename Type>
LinkedList<Type>::LinkedList(Node* head) {
	if (head == nullptr) {
		m_head = nullptr;
	}
	else {
		*m_head = *head;
	}
}

template<typename Type>
LinkedList<Type>::LinkedList(Type* values, size_t size) : m_head(nullptr) {
	for (size_t i = 0; i < size; i++) {
		insert(values[i]);
	}
}

template<typename Type>
LinkedList<Type>::LinkedList(std::initializer_list<Type> values) : m_head(nullptr) {
	for (auto& val : values) {
		insert(val);
	}
}

template<typename Type>
LinkedList<Type>::LinkedList(const LinkedList<Type>& ll) {
	if (ll.m_head == nullptr) {
		m_head = nullptr;
	}
	else {
		if (ll.m_head == nullptr) {
			m_head = nullptr;
			return;
		} 
		if (m_head == nullptr) {
			m_head = new Node();
		}
		*m_head = *(ll.m_head);
	}
}

template<typename Type>
size_t LinkedList<Type>::size() const {
	Node* current = m_head;
	size_t count = 0;
	while (current != nullptr) {
		count++;
		current = current->next;
	}
	return count;
}

template<typename Type>
void LinkedList<Type>::unshift(Type value) {
	if (m_head == nullptr) {
		m_head = new Node(value, nullptr);
		return;
	}

	m_head = new Node(value, m_head);
}

template<typename Type>
void LinkedList<Type>::insert(size_t pos, Type value) {
	if (pos < 0) {
		#ifdef _DEBUG
		throw std::out_of_range("LinkedList index out of bounds.");
		#endif
		return;
	}
	if (pos == 0) {
		return unshift(value);
	}

	Node* current = m_head;
	int iter = 1;
	while (iter < pos) {
		current = current->next;
		iter++;
	}
	current->next = new Node(value, current->next);
}

template<typename Type>
void LinkedList<Type>::insert(Type value) {
	if (m_head == nullptr) {
		m_head = new Node(value, nullptr);
		return;
	}
	if (m_head->next == nullptr) {
		m_head->next = new Node(value, nullptr);
		return;
	}
	Node* current = m_head;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = new Node(value, nullptr);
}

template<typename Type>
bool LinkedList<Type>::remove() {
	if (m_head == nullptr) {
		#ifdef _DEBUG
		throw std::out_of_range("LinkedList is empty. Cannot remove.");
		#endif
		return false;
	}
	Node* temp = m_head;
	m_head = m_head->next;
	delete temp;
	return true;
}

template<typename Type>
bool LinkedList<Type>::remove(Type val) {
	if (m_head == nullptr) {
		#ifdef _DEBUG
		throw std::out_of_range("LinkedList is empty. Cannot remove.");
		#endif
		return false;
	}
	if (m_head->value == val) {
		remove();
	}
	Node* prev = m_head;
	Node* current = prev->next;
	while (current != nullptr) {
		if (current->value == val) {
			prev->next = current->next;
			delete current;
			return true;
		}
		prev = current;
		current = current->next;
	}
	return false;
}

template<typename Type>
void LinkedList<Type>::clear() {
	while (m_head != nullptr) {
		Node* temp = m_head;
		m_head = m_head->next;
		delete temp;
	}
}

template<typename Type>
Type& LinkedList<Type>::get(size_t pos) const {
	if (pos < 0 || pos >= size()) {
		#ifdef _DEBUG
		throw std::out_of_range("LinkedList index out of bounds.");
		#endif
		return m_head->value;
	}
	Node* current = m_head;
	size_t iter = 0;
	while (iter < pos) {
		current = current->next;
		iter++;
	}
	return current->value;
}

template<typename Type>
void LinkedList<Type>::reverse() {
	if (m_head == nullptr || m_head->next == nullptr) {
		return;
	}
	Node* prev = nullptr;
	Node* current = m_head;
	Node* next = current->next;
	while (current != nullptr) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	m_head = prev;
}

#endif
