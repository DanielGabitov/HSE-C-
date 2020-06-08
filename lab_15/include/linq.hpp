#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <iterator>
#include <vector>
#include <functional>

namespace linq {
namespace impl {

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class where_enumerator;
template<typename T, typename F>
class until_enumerator;



//         BASE_ENUMERATOR               //

template<typename T>
class enumerator {
public:

  virtual T operator*() = 0;
  virtual void operator++() = 0;
  virtual operator bool() = 0;

  auto drop(int count) {
    return drop_enumerator<T>(*this, count);
  }

  template<typename U = T, typename F>
  auto select(F func) {
    return select_enumerator< U, T, F>(*this, func);
  }

  template<typename F>
  auto where(F func) {
    return where_enumerator<T, F>(*this, func);
  }

  auto where_neq(T value) {
    return where([value](T x){return x != value;});
  }

  template<typename F>
  auto until(F func) {
    return until_enumerator<T, F>(*this, func);
  }

  auto take(int counter){
    return take_enumerator<T>(*this, counter);
  }

  auto until_eq(T value) {
    return until([value](T x){return x == value;});
  }

  std::vector<T> to_vector() {
    std::vector<T> vec;
    while (*this){
      vec.push_back(this->operator*());
      this->operator++();
    }
    return vec;
  }

  template<typename Iter>
  void copy_to(Iter it) {
    std::vector<T> vec = this->to_vector();
    std::copy(vec.begin(), vec.end(), it);
  }
}; // Enumerator class ENDS.

//         RANGE_ENUMERATOR               //

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:

  range_enumerator(Iter begin, Iter end) 
  : begin(begin), end(end)
  {}

  T operator*(){
    return *begin;
  }

  void operator++(){
    begin++;
  }

  operator bool(){
    return begin != end;
  }

private:
  Iter begin, end;
};

//         DROP_ENUMERATOR               //

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
  
  drop_enumerator(enumerator<T> &parent, int count) 
  : parent(parent), counter(count){}

  virtual T operator*() override {
    return parent.operator*();
  }

  virtual void operator++() override {
    parent.operator++();
  }

  virtual operator bool() override {
    while (parent && counter > 0){
      operator++();
      counter--;
    }
    return (counter == 0) ? parent : false;
  };

private:
  enumerator<T> &parent;
  int counter;
};

//         SELECT_ENUMERATOR               //

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
  select_enumerator(enumerator<U> &parent, F &func)
  : parent(parent), function(std::move(func))
  {}

  T operator*() {
    return function(*parent);
  }

  void operator++(){
    parent.operator++();
  }

  operator bool(){
    return parent;
  }

private:
  enumerator<U> &parent;
  F function;
};

//         WHERE_ENUMERATOR               //

template<typename T, typename F>
class where_enumerator: public enumerator<T>{
public:
  
  where_enumerator(enumerator<T>& parent, F &function)
  : parent(parent), function(std::move(function)){}

  virtual T operator*() override {
    return parent.operator*();
  }

  // Skip useless elements.
  virtual void operator++() override {
    parent.operator++();
  };
  
  virtual operator bool() override {

    if (!parent){
      return false; 
    }

    if (!function(*parent)){
      this->operator++();
      return (*this);
    }

    return true;
  }
private:
  enumerator<T>& parent;
  F function;
};

//          UNTIL ENUMERATOR           //

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:

  until_enumerator(enumerator<T> &parent, F &predicate)
  : parent(parent), predicate(std::move(predicate))
  {}

  virtual T operator*() override {
    return parent.operator*();
  }

  virtual void operator++() override {
    parent.operator++();
  }

  virtual operator bool() override {
    if (parent == false){
      return false;
    }
    if (predicate(*parent) == true){
      is_true = false;
    }
    return is_true;
  }

private:
  enumerator<T> &parent;
  F predicate;
  bool is_true = true;
};

//         TAKE_ENUMERATOR        //

template<typename T>
class take_enumerator: public enumerator<T>{
public:

  take_enumerator(enumerator<T>& parent, int counter)
  : parent(parent), counter(counter)
  {}

  virtual T operator*() override {
    return parent.operator*();
  }

  virtual void operator++() override {
    parent.operator++();
    if (parent){
      counter--;
    }
  }

  virtual operator bool() override {
    return (counter > 0) ? parent : false;
  }

private:
  enumerator<T>&parent;
  int counter;
};

} // namespace impl

template<typename Iterator>
auto from(Iterator begin, Iterator end) {
  return impl::range_enumerator< typename std::iterator_traits<Iterator>::value_type, Iterator>(begin, end);
}

} // namespace linq

#endif