#ifndef VEC_H
#define VEC_H
#include <cstddef>
#include <iostream>
#include <iterator>
#include <exception>
#include <type_traits>

namespace nsl {  // non-standard library...
template <class T>
class vec {
 private:
  T* _vec = nullptr;
  size_t _size;
  size_t _len = 0;

 public:
  class Iterator {
    // iterator tags
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

   private:
    pointer m_ptr;

   public:
    Iterator(pointer ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    // prefix increment
    Iterator& operator++() {
      m_ptr++;
      return *this;
    }

    // postfix increment
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.m_ptr == b.m_ptr;
    }

    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return a.m_ptr != b.m_ptr;
    }
  };
  vec(size_t reserve = 0) {
    _size = sizeof(T) * reserve;
    if (_size) _vec = (T*)malloc(_size);
  }

  ~vec() { free(_vec); }

  T& operator[](size_t i) {
    if (i >= _len) throw std::out_of_range("out of bounds vec access");
    return _vec[i];
  }

  T& get_unsafe(size_t i) { return _vec[i]; }

  void push(T val) {
    size_t type_size = sizeof(T);

    if (_size == 0) {
      _size = type_size;
      _vec = (T*)malloc(_size);
    } else if (_size <= _len * type_size) {
      _size += type_size;
      _vec = (T*)realloc(_vec, _size);
    }

    _vec[_len] = val;
    _len++;
  }

  /// decrements the length & will shrink the vector unless mem has
  /// been reserved
  void pop() {
    if (_len * sizeof(T) == _size) {
      _size -= sizeof(T);
      _vec = (T*)realloc(_vec, _size);
    }
    _len--;
  }

  size_t size() { return _size; }
  size_t len() { return _len; }
  const T* ptr() { return _vec; };

  // iterator methods
  Iterator begin() { return Iterator(&_vec[0]); }
  Iterator end() { return Iterator(&_vec[_len]); }

  vec& operator=(const char* str) noexcept {
    static_assert(std::is_same<T, char>::value,
                  "cannot assign "
                  "string to non string vector");

    int str_len = 0;
    while (str[str_len] != '\0') str_len++;

    if (_len != str_len) {  // shrink or grow vec to fit new string
      _size = str_len + 1;
      _vec = (T*)realloc(_vec, str_len + 1);
    }

    _len = 0;

    for (int i = 0; i < str_len; i++) {
      push(str[i]);
    }

    push('\0');

    return *this;
  }
};

class str {
 private:
  size_t _len;
  vec<char> _vec;

 public:
  str(size_t reserve = 0) : _vec(reserve) {}
  str(const char* str) {
    _vec = str;
    _len = _vec.len() - 1;
  }

  str& operator=(const char* str) noexcept {
    _vec = str;
    _len = _vec.len() - 1;
    return *this;
  }

  char& operator[](size_t index) { return _vec[index]; }

  friend std::ostream& operator<<(std::ostream& os, str& s) {
    return os << s.ptr();
  }

  void append(const char* str) {
    _vec.pop();  // remove null terminator

    int str_len = 0;
    while (str[str_len] != '\0') {
      _vec.push(str[str_len]);
      str_len++;
      _len++;
    }

    _vec.push('\0');
  }

  const char* ptr() { return _vec.ptr(); }

  size_t len() { return _len; }

  vec<char>::Iterator begin() { return vec<char>::Iterator(&_vec[0]); }
  vec<char>::Iterator end() { return vec<char>::Iterator(&_vec[_len]); }
};
}  // namespace nsl

#endif  // VEC_H
