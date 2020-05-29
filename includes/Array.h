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

#ifndef DS_ARRAY_H
#define DS_ARRAY_H

#include <initializer_list>
#include <stdexcept>
#include <memory>

template<typename Type, size_t N>
class Array
{
  public:
    Array();
    Array(Type* data, size_t size);
    Array(std::initializer_list<Type> data);
    Array(const Array<Type, N>& array);
    ~Array();
    Array& operator=(const Array&);

    Type& at(size_t pos) const;
    Type& operator[](size_t pos) const { at(pos); }
    Type& front() const { return at(0); }
    Type& back() const { return at(m_last); }
    Type* data() const { return m_data.get(); }

    size_t empty() const { return m_last == -1; }
    size_t size() const { return m_last + 1; }
    size_t max_size() const { return N; }

    void fill(Type value) noexcept;
    void swap(size_t pos1, size_t pos2) noexcept;

  private:
    std::unique_ptr<Type[]> m_data;
    size_t m_last;
};

template<typename Type, size_t N>
Array<Type, N>::Array() : m_last(-1) {
    m_data = std::make_unique<Type[]>(N);
    static_assert(N > 0, "Array size cannot be 0 or negatize");
}

template<typename Type, size_t N>
Array<Type, N>::Array(Type* data, size_t size) {
    m_data = std::make_unique<Type[]>(N);
    m_last = 0;
    while (m_last < size && m_last < N) {
        m_data[m_last] = data[m_last];
        m_last++;
    }
    m_last--;
}

template<typename Type, size_t N>
Array<Type, N>::Array(std::initializer_list<Type> data) {
    m_data = std::make_unique<Type[]>(N);
    m_last = 0;
    for (auto it = data.begin(); it != data.end() && m_last < N; it++) {
        m_data[m_last++] = *it;
    }
    m_last--;
}

template<typename Type, size_t N>
Array<Type, N>::Array(const Array<Type, N>& array) {
    m_data = std::make_unique<Type[]>(N);
    m_last = 0;
    while (m_last <= array.m_last) {
        m_data[m_last] = array[m_last];
        m_last++;
    }
    m_last--;
}

template<typename Type, size_t N>
Array<Type, N>::~Array() {
    m_data.reset();
    m_last = -1;
}

template<typename Type, size_t N>
Array<Type, N>& Array<Type, N>::operator=(const Array& array) {
    m_data = std::make_unique<Type[]>(N);
    m_last = 0;
    while (m_last <= array.m_last) {
        m_data[m_last] = array[m_last];
        m_last++;
    }
    return *this;
}

template<typename Type, size_t N>
Type& Array<Type, N>::at(size_t pos) const {
    if (m_last == -1 || pos < 0 || pos > m_last) {
#ifdef _DEBUG
        throw std::out_of_range("Array index out of bounds");
#endif// _DEBUG
    }
    return m_data[pos];
}
template<typename Type, size_t N>
void Array<Type, N>::fill(Type value) noexcept {
    m_last = 0;
    while (m_last < N) {
        m_data[m_last++] = value;
    }
    m_last = N - 1;
}

template<typename Type, size_t N>
void Array<Type, N>::swap(size_t pos1, size_t pos2) noexcept {
    Type temp = at(pos1);
    at(pos1) = at(pos2);
    at(pos2) = temp;
}

template<typename Type, size_t N>
bool operator==(const Array<Type, N>& array1, const Array<Type, N>& array2) {
    for (size_t i = 0; i < array1.size(); i++) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

template<typename Type, size_t N>
bool operator!=(const Array<Type, N>& array1, const Array<Type, N>& array2) {
    return !(array1 == array2);
}

template<typename Type, size_t N>
bool operator<(const Array<Type, N>& array1, const Array<Type, N>& array2) {
    for (size_t i = 0; i < array1.size(); i++) {
        if (array1[i] > array2[i]) {
            return false;
        }
        else if (array1[i] < array2[i]) {
            return true;
        }
    }
    return false;
}

template<typename Type, size_t N>
bool operator<=(const Array<Type, N>& array1, const Array<Type, N>& array2) {
    for (size_t i = 0; i < array1.size(); i++) {
        if (array1[i] > array2[i]) {
            return false;
        }
        else if (array1[i] < array2[i]) {
            return true;
        }
    }
    return true;
}

template<typename Type, size_t N>
bool operator>(const Array<Type, N>& array1, const Array<Type, N>& array2) {
    return !(array1 <= array2);
}

template<typename Type, size_t N>
bool operator>=(const Array<Type, N>& array1, const Array<Type, N>& array2) {
    return !(array1 < array2);
}

#endif
