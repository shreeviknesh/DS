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

template <typename Type>
class BST {
public:
    class Node;

    BST() : m_root(nullptr) {}
    BST(Node* root) : m_root(root) {}
    BST(std::initializer_list<Type> values);
    ~BST();

    void insert(Type value);
    void remove(Type value);
private:
    Node* m_root;
    void deleteRecursive(Node* node);
    void insertRecursive(Node* node, Type value);
};

template <typename Type>
class BST<Type>::Node {
    Type value;
    Node* left;
    Node* right;

    Node() : value(Type()), left(nullptr), right(nullptr) {}
    Node(_value) : value(_value), left(nullptr), right(nullptr) {}

    friend class BST<Type>;
};

template<typename Type>
BST<Type>::BST(std::initializer_list<Type> values) {
    for (Type value : values) {
        insert(value);
    }
}

template<typename Type>
BST<Type>::~BST() {
    deleteRecursive(m_root);
}

template<typename Type>
void BST<Type>::insert(Type value) {
    if (m_root == nullptr) {
        m_root = Node(value);
    }
}

template<typename Type>
void BST<Type>::deleteRecursive(Node* node) {
    if (node == nullptr) {
        return;
    }

    Node* temp = node;
    deleteRecursive(node->left);
    deleteRecursive(node->right);
    delete temp;

}