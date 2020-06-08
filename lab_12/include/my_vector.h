#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <fstream>
#include <exception>

namespace my_vector {

template<typename T>
class my_vector {
public:
  my_vector();
  explicit my_vector(std::size_t n);
  my_vector(const my_vector &other);
  my_vector(my_vector &&other);
  my_vector& operator=(const my_vector &other);
  my_vector& operator=(my_vector &&other) noexcept;
  ~my_vector() noexcept;

  size_t size() const noexcept;
  size_t capacity() const noexcept;
  bool empty() const noexcept;

  void resize(std::size_t n);
  void reserve(std::size_t n);

  T& operator[](std::size_t index) &;
  const T& operator[](std::size_t index) const &;

  void push_back(T t);
  void pop_back();
  void clear() noexcept;
private:
  size_t _capacity;
  size_t _size;
  T* _array;
  void swap(my_vector& b) noexcept;
};

class my_vector_exception : public std::exception {
private:
  std::string _error_command;
public:
  my_vector_exception(std::string);
  const char * what() const noexcept override;
};

}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_