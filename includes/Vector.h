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
#include <memory>

template <typename Type>
class Vector {
public:
    Vector();
    Vector(size_t size);
    Vector(size_t size, Type* values);
    Vector(std::initializer_list<Type> values);
    Vector(const Vector<Type>& vector);
    ~Vector();
    Vector<Type>& operator = (const Vector<Type>& vector);

    Type& get(size_t pos) const;
    Type& operator [] (size_t pos) const { return get(pos); }
    Type at(size_t pos) const { return get(pos); }

    size_t size() const noexcept { return m_last + 1; }
    size_t max_size() const noexcept { return m_size; }
    bool empty() const noexcept { return (m_size == 0); }
    void reserve(size_t size);
    void shrink_to_fit();

    void clear() noexcept;
    void insert(size_t pos, const Type& value);
    void insert(size_t pos, const Vector<Type>& values);
    void insert(size_t pos, std::initializer_list<Type> values);
    void erase(size_t pos);
    void erase(size_t pos1, size_t pos2);
    void push_back(const Type& value);
    void pop_back() { m_last--; }
    void resize(size_t targetSize); // shrink or expand
    void resize(size_t targetSize, Type value); // only expand
    void swap(size_t pos1, size_t pos2);
    void swap(Vector<Type>& other);

    void assign(size_t count, const Type& value);
    void assign(std::initializer_list<Type> values);

    Type front() const;
    Type  back() const;
    Type* data() const noexcept { return m_data.get(); }


private:
    std::unique_ptr<Type[]> m_data;
    size_t m_size;
    size_t m_last;
};

template<typename Type>
inline Vector<Type>::Vector() : m_data(nullptr), m_size(0), m_last(-1) {}

template<typename Type>
inline Vector<Type>::Vector(size_t size) : m_size(size), m_last(-1) {
    m_data = std::make_unique<Type[]>(m_size);
}

template<typename Type>
Vector<Type>::Vector(size_t size, Type* values) : m_size(size) {
    m_data = std::make_unique<Type[]>(m_size);
    for (m_last = 0; m_last < size; m_last++) {
        m_data[m_last] = values[m_last];
    }
    m_last--;
}

template<typename Type>
Vector<Type>::Vector(std::initializer_list<Type> values) {
    m_data = std::make_unique<Type[]>(values.size());
    m_size = 0;
    for (Type value : values) {
        m_data[m_size++] = value;
    }
    m_last = m_size - 1;
}

template<typename Type>
Vector<Type>::Vector(const Vector<Type>& vector) {
    m_size = vector.m_size;
    m_data = std::make_unique<Type[]>(m_size);
    m_last = vector.m_last;
    for (size_t i = 0; i <= m_last; i++) {
        m_data[i] = vector[i];
    }
}

template<typename Type>
inline Vector<Type>::~Vector() {
    clear();
}

template<typename Type>
Vector<Type>& Vector<Type>::operator = (const Vector<Type>& vector) {
    clear();
    m_size = vector.m_size;
    m_data = std::make_unique<Type[]>(m_size);
    m_last = vector.m_last;
    for (size_t i = 0; i <= m_last; i++) {
        m_data[i] = vector[i];
    }
    return *this;
}

template<typename Type>
Type& Vector<Type>::get(size_t pos) const {
    if (pos < 0 || pos > m_last) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector index out of bounds");
        #endif // _DEBUG
    }
    return m_data[pos];
}

template<typename Type>
void Vector<Type>::reserve(size_t size) {
    Type* values = m_data.release();
    m_data = std::make_unique<Type[]>(size);
    m_size = size;
    for (size_t i = 0; i <= m_last; i++) {
        m_data[i] = values[i];
    }
}

template<typename Type>
void Vector<Type>::shrink_to_fit() {
    if (m_last == m_size - 1) {
        return;
    }
    Type* values = m_data.release();
    m_data = std::make_unique<int[]>(m_last + 1);
    for (size_t i = 0; i <= m_last; i++) {
        m_data[i] = values[i];
    }
    m_size = m_last + 1;
}

template<typename Type>
inline void Vector<Type>::clear() noexcept {
    if (m_size != 0) {
        m_data.reset();
        m_size = 0;
        m_last = -1;
    }
}

template<typename Type>
inline void Vector<Type>::insert(size_t pos, const Type& value) {
    if (pos < 0 || pos > m_last) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector index out of bounds");
        #endif // _DEBUG
        return;
    }
    if (m_last == m_size - 1) {
        Type* values = m_data.release();
        m_data = std::make_unique<Type[]>(m_size + 1);
        for (size_t i = 0; i < pos; i++) {
            m_data[i] = values[i];
        }
        for (size_t i = pos; i <= m_last; i++) {
            m_data[i + 1] = values[i];
        }
        m_size++;
        m_last = m_size - 1;
    }
    else {
        for (size_t i = m_last; i >= pos; i--) {
            m_data[i + 1] = m_data[i];
        }
        m_last++;
    }
    m_data[pos] = value;
}

template<typename Type>
void Vector<Type>::insert(size_t pos, const Vector<Type>& vector) {
    if (pos < 0 || pos > m_last + 1) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector index out of range");
        #endif // _DEBUG
        return;
    }
    size_t vector_size = vector.size();
    if (m_last + vector_size >= m_size) {
        Type* values = m_data.release();
        m_data = std::make_unique<int[]>(m_size + vector_size);
        for (size_t i = 0; i < pos; i++) {
            m_data[i] = values[i];
        }
        for (size_t i = 0; i < vector_size; i++) {
            m_data[pos + i] = vector.m_data[i];
        }
        for (size_t i = pos; i < m_size; i++) {
            m_data[i + vector_size] = values[i];
        }
        m_size += vector_size;
        m_last = m_size - 1;
    }
    else {
        Type* data = new Type[m_last + 1];
        for (size_t i = 0; i <= m_last; i++) {
            data[i] = m_data.get()[i];
        }
        for (size_t i = pos; i <= m_last; i++) {
            m_data[i + vector_size] = data[i];
        }
        size_t index = pos;
        for (size_t i = 0; i < vector_size; i++) {
            m_data[pos + i] = vector.m_data[i];
        }
        m_last += vector_size;
    }
}

template<typename Type>
void Vector<Type>::insert(size_t pos, std::initializer_list<Type> values) {
    if (pos < 0 || pos > m_last + 1) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector index out of range");
        #endif // _DEBUG
        return;
    }
    size_t list_size = values.size();
    if (m_last + list_size >= m_size) {
        Type* data = m_data.release();
        m_data = std::make_unique<int[]>(m_size + list_size);
        size_t index = 0;
        for (; index < pos; index++) {
            m_data[index] = data[index];
        }
        for (Type value : values) {
            m_data[index++] = value;
        }
        for (size_t i = pos; i < m_size; i++) {
            m_data[index++] = data[i];
        }
        m_size += list_size;
        m_last += list_size;
    }
    else {
        Type* data = new Type[m_last + 1];
        for (size_t i = 0; i <= m_last; i++) {
            data[i] = m_data.get()[i];
        }
        for (size_t i = pos; i <= m_last; i++) {
            m_data[i + list_size] = data[i];
        }
        size_t index = pos;
        for (Type value : values) {
            m_data[index++] = value;
        }
        m_last += list_size;
    }
}

template<typename Type>
void Vector<Type>::erase(size_t pos) {
    for (size_t i = pos; i < m_last; i++) {
        m_data[i] = m_data[i + 1];
    }
    m_last--;
}

template<typename Type>
void Vector<Type>::erase(size_t pos1, size_t pos2) {
    if (pos1 < 0 || pos2 < 0 || pos1 > m_last || pos2 > m_last || pos1 > pos2) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector index out of range");
        #endif // _DEBUG
        return;
    }
    if (pos1 == pos2) {
        return erase(pos1);
    }
    size_t temp_last = m_last - (pos2 - pos1 + 1);
    for (size_t i = pos2 + 1; i <= m_last; i++) {
        m_data[pos1++] = m_data[i];
    }
    m_last = temp_last;
}

template<typename Type>
void Vector<Type>::assign(size_t count, const Type& value) {
    clear();
    m_size = count;
    m_last = m_size - 1;
    m_data = std::make_unique<Type[]>(m_size);
    for (size_t i = 0; i < m_size; i++) {
        m_data[i] = value;
    }
}

template<typename Type>
void Vector<Type>::assign(std::initializer_list<Type> values) {
    clear();
    m_size = values.size();
    m_last = -1;
    m_data = std::make_unique<Type[]>(m_size);
    for (Type val : values) {
        m_data[++m_last] = val;
    }
}

template<typename Type>
Type Vector<Type>::front() const {
    if (m_size == 0) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector index out of bounds");
        #endif // _DEBUG
        return Type();
    }
    return m_data[0];
}

template<typename Type>
Type Vector<Type>::back() const {
    if (m_size == 0) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector index out of bounds");
        #endif // _DEBUG
        return Type();
    }
    return m_data[m_last];
}

template<typename Type>
void Vector<Type>::push_back(const Type& value) {
    if (m_last == m_size - 1) {
        Type* values = m_data.release();
        m_data = std::make_unique<Type[]>(m_size + 1);
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = values[i];
        }
        m_size++;
    }
    m_data[++m_last] = value;
}

template<typename Type>
void Vector<Type>::resize(size_t targetSize) {
    if (targetSize < 0) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector size cannot be negative");
        #endif // _DEBUG
        return;
    }
    Type value = Type();
    if (targetSize == 0) {
        clear();
        return;
    }
    if (targetSize < size()) {
        m_last = targetSize - 1;
        shrink_to_fit();
        return;
    }
    if (targetSize > m_size) {
        reserve(targetSize);
    }
    for (size_t i = m_last + 1; i < targetSize; i++) {
        m_data[i] = value;
    }
    m_last = targetSize - 1;
}

template<typename Type>
void Vector<Type>::resize(size_t targetSize, Type value) {
    if (targetSize <= m_last) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector cannot shrink - use resize(size_t) instead.");
        #endif // _DEBUG
        return;
    }
    if (targetSize > m_size) {
        reserve(targetSize);
    }
    for (size_t i = m_last + 1; i < targetSize; i++) {
        m_data[i] = value;
    }
    m_last = targetSize - 1;
}

template<typename Type>
void Vector<Type>::swap(size_t pos1, size_t pos2) {
    if (pos1 < 0 || pos2 < 0 || pos1 > m_last || pos2 > m_last) {
        #ifdef _DEBUG
        throw std::out_of_range("Vector index out of bounds");
        #endif // _DEBUG
        return;
    }
    Type temp = m_data[pos1];
    m_data[pos1] = m_data[pos2];
    m_data[pos2] = temp;
}

template<typename Type>
inline void Vector<Type>::swap(Vector<Type>& other) {
    m_data.swap(other.m_data);

    size_t temp = m_last;
    m_last = other.m_last;
    other.m_last = temp;

    temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;
}
