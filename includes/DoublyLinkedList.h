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

#pragma once
#include <initializer_list>
#include <stdexcept>

template <typename Type>
class DoublyLinkedList {
public:
	class Node;

	DoublyLinkedList();
	DoublyLinkedList(Type values[], size_t size);
	DoublyLinkedList(std::initializer_list<Type> values);
	~DoublyLinkedList() { clear(); }

	inline bool empty() const { return (m_head == nullptr); }
	inline Node* head() const { return m_head; }
	inline Node* tail() const { return m_tail; }

	void insert(Type value);
	void unshift(Type value);
	void insertBefore(Node* node, Type value);
	void insertAfter(Node* node, Type value);

	// Inserts a value such that the list is in ascending order
	void priorityInsert(Type value);

	Type getHead() const;
	Type getTail() const;

	bool removeHead();
	bool removeTail();
	bool remove(DoublyLinkedList<Type>::Node* node);
	bool remove(Type value);

	void clear();

private:
	Node* m_head;
	Node* m_tail;
};

template <typename Type>
class DoublyLinkedList<Type>::Node {
public:
	Type value;
	Node* next;
	Node* prev;

	Node() : value(Type()), next(nullptr), prev(nullptr) {}
	Node(Type value_, Node* next_ = nullptr, Node* prev_ = nullptr) : value(value_), next(next_), prev(prev_) {}
};

template <typename Type>
DoublyLinkedList<Type>::DoublyLinkedList() : m_head(nullptr), m_tail(nullptr) {}

template <typename Type>
DoublyLinkedList<Type>::DoublyLinkedList(Type values[], size_t size) {
	DoublyLinkedList();
	for (size_t i = 0; i < size; i++) {
		insert(values[i]);
	}
}

template <typename Type>
DoublyLinkedList<Type>::DoublyLinkedList(std::initializer_list<Type> values) {
	DoublyLinkedList();
	for (Type val : values) {
		insert(val);
	}
}

template <typename Type>
void DoublyLinkedList<Type>::insert(Type value) {
	if (m_tail == nullptr) {
		m_head = new Node(value);
		m_tail = m_head;
		return;
	}
	insertAfter(m_tail, value);
}

template <typename Type>
void DoublyLinkedList<Type>::unshift(Type value) {
	if (m_head == nullptr) {
		m_tail = new Node(value);
		m_head = m_tail;
		return;
	}
	insertBefore(m_head, value);
}


template <typename Type>
void DoublyLinkedList<Type>::insertBefore(Node* node, Type value) {
	Node* newNode = new Node(value);
	if (node == nullptr) {
		#ifdef _DEBUG
		throw std::invalid_argument("Cannot insert before node as DoublyLinkedList is empty");
		#endif
		return;
	}
	if (node->prev == nullptr) {
		newNode->next = m_head;
		m_head->prev = newNode;
		m_head = newNode;
		return;
	}
	newNode->prev = node->prev;
	node->prev = newNode;
	newNode->prev = node;
	newNode->prev->next = newNode;
}

template <typename Type>
void DoublyLinkedList<Type>::insertAfter(Node* node, Type value) {
	Node* newNode = new Node(value);
	if (node == nullptr) {
		#ifdef _DEBUG
		throw std::invalid_argument("Cannot insert after node as DoublyLinkedList is empty");
		#endif
		return;
	}
	if (node->next == nullptr) {
		newNode->prev = m_tail;
		m_tail->next = newNode;
		m_tail = newNode;
		return;
	}
	newNode->next = node->next;
	node->next = newNode;
	newNode->prev = node;
	newNode->next->prev = newNode;
}

template<typename Type>
void DoublyLinkedList<Type>::priorityInsert(Type value) {
	if (empty()) {
		unshift(value);
		return;
	}
	Node* temp = m_head;
	while (temp != nullptr && temp->value < value) {
		temp = temp->next;
	}
	if (temp == nullptr) {
		insertAfter(m_tail, value);
		return;
	}
	insertBefore(temp, value);
}

template <typename Type>
Type DoublyLinkedList<Type>::getHead() const {
	if (m_head == nullptr) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot remove head as DoublyLinkedList is empty.");
		#endif
		return Type();
	}
	return m_head->value;
}

template <typename Type>
Type DoublyLinkedList<Type>::getTail() const {
	if (m_tail == nullptr) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot remove head as DoublyLinkedList is empty.");
		#endif
		return Type();
	}
	return m_tail->value;
}

template <typename Type>
bool DoublyLinkedList<Type>::removeHead() {
	if (m_head == nullptr) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot remove head as DoublyLinkedList is empty.");
		#endif
		return false;
	}
	if (m_tail == m_head) {
		delete m_head;
		m_head = m_tail = nullptr;
		return true;
	}
	Node* toDelete = m_head;
	m_head = m_head->next;
	if (m_head != nullptr) {
		m_head->prev = nullptr;
	}
	delete toDelete;
	return true;
}

template <typename Type>
bool DoublyLinkedList<Type>::removeTail() {
	if (m_tail == nullptr) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot remove head as DoublyLinkedList is empty.");
		#endif
		return false;
	}
	if (m_tail == m_head) {
		delete m_tail;
		m_head = m_tail = nullptr;
		return true;
	}
	Node* toDelete = m_tail;
	m_tail = m_tail->prev;
	if (m_tail != nullptr) {
		m_tail->next = nullptr;
	}
	delete toDelete;
	return true;
}

template <typename Type>
bool DoublyLinkedList<Type>::remove(DoublyLinkedList<Type>::Node* node) {
	if (node->prev == nullptr) {
		return removeHead();
	}
	if (node->next == nullptr) {
		return removeTail();
	}
	Node* prev = node->prev;
	Node* next = node->next;
	prev->next = next;
	next->prev = prev;
	delete node;
	return true;
}

template <typename Type>
bool DoublyLinkedList<Type>::remove(Type value) {
	if (m_head == nullptr) {
		#ifdef _DEBUG
		throw std::out_of_range("Cannot remove head as DoublyLinkedList is empty.");
		#endif
		return false;
	}
	Node* current = m_head;
	while (current != nullptr) {
		if (current->value == value) {
			return remove(current);
		}
		current = current->next;
	}
	return false;
}

template<typename Type>
void DoublyLinkedList<Type>::clear() {
	while (m_head != nullptr) {
		removeHead();
	}
}
