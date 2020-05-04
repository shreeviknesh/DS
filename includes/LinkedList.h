#pragma once
#include "utils\Node.h"
#include <initializer_list>
#include <stdexcept>

template <typename Type>
class LinkedList {
private:
	Node<Type>* m_head;
	size_t m_size;

public:
	LinkedList() : m_head(nullptr), m_size(0) {}

	LinkedList(Node<Type>* head, size_t size) {
		if (size < 0) {
			#ifdef _DEBUG
				throw std::out_of_range("LinkedList size cannot be negative");
			#endif
			m_head = nullptr;
			m_size = 0;
			return;
		}

		*m_head = *head;
		m_size = size;
	}

	LinkedList(Type* array, size_t size) : m_head(nullptr), m_size(0) {
		for (size_t i = 0; i < size; i++) {
			insert(array[i]);
		}
	}
	
	LinkedList(std::initializer_list<Type> array) : m_head(nullptr), m_size(0) {
		for (auto& val : array) {
			insert(val);
		}
	}

	~LinkedList() {
		Node<Type>* temp;
		while (m_head != nullptr) {
			temp = m_head;
			m_head = m_head->next;
			delete temp;
		}
	}

	// Get size of the LinkedList
	size_t size() const {
		return m_size;
	}

	// Insert an element in the beginning
	void unshift(Type value) {
		if (m_head == nullptr) {
			m_head = new Node<Type>(value, nullptr);
			m_size = 1;
			return;
		}

		m_head = new Node<Type>(value, m_head);
		m_size++;
	}

	// Insert an element at pos
	void insert(size_t pos, Type value) {
		if (pos < 0 || pos > m_size) {
			#ifdef _DEBUG
				throw std::out_of_range("LinkedList index out of bounds.");
			#endif
			return;
		}

		if (pos == 0) {
			return unshift(value);
			//return;
		}

		Node<Type>* current = m_head;
		int iter = 1;

		while (iter < pos) {
			current = current->next;
			iter++;
		}
		
		Node<Type>* newNode = new Node<Type>(value, current->next);
		current->next = newNode;
		m_size++;
	}

	// Insert an element at the end
	void insert(Type value) {
		if (m_head == nullptr) {
			m_head = new Node<Type>(value, nullptr);
			m_size++;
			return;
		}

		insert(m_size, value);
	}

	// Remove the head element
	bool remove() {
		if (m_head == nullptr) {
			#ifdef _DEBUG
				throw std::out_of_range("LinkedList is empty. Cannot remove.");
			#endif
			return false;
		}

		Node<Type>* temp = m_head;
		m_head = m_head->next;
		m_size--;
		delete temp;
		return true;
	}

	// Remove the first element with value = val
	bool remove(Type val) {
		if (m_head == nullptr) {
			#ifdef _DEBUG
				throw std::out_of_range("LinkedList is empty. Cannot remove.");
			#endif
			return false;
		}
		
		if (m_head->value == val) {
			Node<Type>* toDelete = m_head;
			m_head = m_head->next;
			delete toDelete;
			m_size--;
			return true;
		}

		if (m_head->next == nullptr) {
			return false;
		}

		Node<Type>* prev = m_head;
		Node<Type>* current = prev->next;

		while (current != nullptr) {
			if (current->value == val) {
				prev->next = current->next;
				delete current;
				m_size--;
				return true;
			}

			prev = current;
			current = current->next;
		}

		return false;
	}

	// remove the pos-th element 
	bool removeIndex(size_t pos) {
		if (m_head == nullptr) {
			#ifdef _DEBUG
				throw std::out_of_range("LinkedList is empty. Cannot remove.");
			#endif
			return false;
		}

		if (pos < 0 || pos >= m_size) {
			#ifdef _DEBUG
				throw std::out_of_range("LinkedList index out of bounds.");
			#endif
			return false;
		}

		if (pos == 0) {
			return remove();
		}

		Node<Type>* prev = getNode(pos - 1);
		Node<Type>* element = getNode(pos);

		prev->next = element->next;
		delete element;
		m_size--;
		return true;
	}

	// Check if the LinkedList is empty?
	bool isEmpty() const { return (m_head == nullptr); }

	// Clear the elements of the LinkedList
	void clear() {
		while (!isEmpty()) {
			remove();
		}
	}

	// Set the pos-th element
	void set(size_t pos, Type value) {
		getNode(pos)->value = value;
	}

	// Get the node at pos in 0-based indexing
	Node<Type>* getNode(size_t pos) const {
		if (pos < 0 || pos >= m_size) {
			#ifdef _DEBUG
				throw std::out_of_range("LinkedList index out of bounds.");
			#endif
			return nullptr;
		}

		Node<Type>* current = m_head;
		size_t iter = 0;

		while (iter < pos) {
			current = current->next;
			iter++;
		}

		return current;
	}

	// Get the element at pos
	Type get(size_t pos) const {
		return getNode(pos)->value;
	}

	// Array index operator
	Type& operator [](size_t pos) {
		return getNode(pos)->value;
	}
};