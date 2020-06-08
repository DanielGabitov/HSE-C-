#include <new>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

namespace my_vector{ // START of my_vector NAMESPASE

size_t successful_allocs = 0;

size_t static get_capacity(size_t n) {
  return pow(2, ceil(log(n) / log(2)));
}

template <typename T>
void delete_array_el(size_t dest, size_t size, T *array) {
  for (size_t i = dest; i > dest - size; i--){
    array[i - 1].~T();
  }
}

template <typename T>
void create_array_el(size_t dest, size_t size, T *array){
  for (size_t i = dest; i < dest + size; i++){
    new (&array[i]) T();
    successful_allocs++;
  }
}

template <typename T>
void create_copy_array_el(size_t dest, size_t size, T *array, T *other_array){
  for (size_t i = dest; i < dest + size; i++){
    new (&array[i]) T(other_array[i]);
    successful_allocs++;
  }
}

template <typename T>
void my_vector<T>::swap(my_vector &other) noexcept{
  std::swap(_array, other._array);
  std::swap(_capacity, other._capacity);
  std::swap(_size, other._size);
}

template <typename T>
my_vector<T>::my_vector()
  : _capacity(0)
  , _size(0)
  , _array(nullptr)
{}

template<typename T>
void my_vector<T>::clear() noexcept{
  delete_array_el(_size, _size, _array);
  _size = 0;
}

template<typename T>
my_vector<T>::~my_vector() noexcept{
  clear();
  delete [] reinterpret_cast<char*>(_array);
}

template <typename T>
my_vector<T>::my_vector(size_t n)
  : _capacity(get_capacity(n))
  , _size(n)
  , _array(reinterpret_cast<T *> (new char [n * sizeof (T)])){

  try {
    create_array_el<T>(0, _size, _array);
  } catch (...){
    delete_array_el<T>(successful_allocs, successful_allocs, _array);
    delete [] reinterpret_cast <char *> (_array);
    throw my_vector_exception("Something went wrong in deafault-constructor.");
  }
  successful_allocs = 0;
}

template <typename T>
my_vector<T>::my_vector(const my_vector& other)
  : _capacity(other._capacity)
  , _size(other._size)
  , _array(reinterpret_cast<T *> (new char [other._capacity * sizeof (T)])){
  
  try{
    create_copy_array_el<T>(0, _size, _array, other._array);
  } catch(...){
    delete_array_el<T>(successful_allocs, successful_allocs, _array);
    delete [] reinterpret_cast <char *> (_array);
    throw my_vector_exception("Something went wrong in copy-constructor.");
  }
  successful_allocs = 0;
  
}

template <typename T>
my_vector<T>::my_vector( my_vector &&other){
  std::swap(_capacity, other._capacity);
  std::swap(_size, other._size);
  std::swap(_array, other._array);
}

template <typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector &other){
  my_vector tmp(other);
  tmp.swap(*this);
  return *this;
}

template <typename T>
my_vector<T>& my_vector<T>::operator=(my_vector &&other) noexcept{
  swap(other);
  return *this;
}

template <typename T>
void my_vector<T>::reserve(size_t n){
  if (_capacity >= n){
    return;
  }
  size_t old_cap = _capacity; 
  _capacity = get_capacity(n);     // Для того чтобы сделать копию вектора с большим capacity,  
  try{                             // содержащую все те же элементы, что и this, изменим капасити
    my_vector new_vector  = *this; //  this, а затем воспользуемся конструктором копирования, 
    *this = std::move(new_vector); // который создаст копию, которая нам и была нужна
  } catch(...){
    _capacity = old_cap;
    throw my_vector_exception("Something went wrong in reserve function.");
  }
}

template <typename T>
void my_vector<T>::resize(size_t n){
  try {
    if (n > _size){
      my_vector<T> new_vector(*this);
      new_vector.reserve(n);
      create_array_el<T>(_size, n - _size, new_vector._array);
      new_vector._size = n;
      *this = std::move(new_vector);
      return;
    }

    my_vector new_vector(*this);
    delete_array_el<T>(_size, _size - n, _array);
    new_vector._size = n;
    *this = std::move(new_vector);
  } catch (...){
    throw my_vector_exception("Something went wrong in resize method.");
  }
}

template <typename T>
void my_vector<T>::pop_back(){
  if (_size == 0){
    throw my_vector_exception("Pop from empty vector.");;
  }
  _array[--_size].~T();
}

template<typename T>
void my_vector<T>::push_back(T t){
  my_vector new_vector(*this);
  try {
    new_vector.reserve(new_vector._size + 1);
    new (&new_vector._array[new_vector._size++]) T(t);
  } catch(...){
    throw my_vector_exception("Unsuccessful push back.");
  }
  new_vector.swap(*this);
}

template <typename T>
T& my_vector<T>::operator[](size_t index) &{
  if ( index >= _size){
    throw my_vector_exception("Index out of range.");
  }
  return _array[index];
}

template <typename T>
const T& my_vector<T>::operator[](size_t index) const & {
  if ( index >= _size){
    throw my_vector_exception("Index out of range.");
  }
  return _array[index];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const my_vector<T>& vector){
  for (size_t i = 0; i < vector.size() - 1; i++){
    os << vector[i] << ' ';
  }
  os << vector[vector.size() - 1];
  return os;
}

template<typename T>
size_t my_vector<T>::size() const noexcept{
  return _size;
}

template<typename T>
bool my_vector<T>::empty() const noexcept{
  return _size == 0;
}

template<typename T>
size_t my_vector<T>::capacity() const noexcept{
  return _capacity;
}

my_vector_exception::my_vector_exception(std::string error_command)
  : _error_command(error_command)
{}

const char * my_vector_exception::what() const noexcept{
  return _error_command.c_str();
}


} // END of my_vector NAMESPACE