#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <cstring>
#include <assert.h>
#include "my_vector.h"

namespace product {

class Product {
public:
  Product(const char* name, int quantity, double price);
  friend std::ostream& operator<<(std::ostream& os, const Product&);
  bool operator==(const Product&);
  ~Product() = default;
  Product& operator=(Product&) = default;
    Product& operator=(Product&&) = delete;
  Product(const Product&) = default;
  Product(Product&&) = delete;
private:
  const char *_name;  // Массив чаров
  int _quantity;
  double _price;
};

void print(const my_vector::my_vector<Product>& v) {
  std::cout << v << std::endl;
}

bool Product::operator==(const Product& other){
  return (
    strcmp(_name, other._name) == 0
    and _price == other._price 
    and _quantity == other._quantity
    );
}

Product::Product(const char* name, int quantity, double price)
  : _name(name)
  , _quantity(quantity)
  , _price(price)
{}

std::ostream& operator<<(std::ostream& os, const Product& p){
  os << p._name << ' ' << p._quantity << ' ' << p._price << ' ';
  return os;
}
}  // namespace product

namespace test{ // NAMESPACE tests STARTS

template <typename T>
void test_default_constructor(){
  my_vector::my_vector<T> v (5);
  for (size_t i = 0; i < 5; i++){
    assert (v[i] == T());
  }
  assert(v.size() == 5);
  assert(v.capacity() == 8);
}

template <typename T>
void test_resize(T a, T b){
  my_vector::my_vector<T> v(3);
  v[2] = a;
  v.resize(5);
  assert(v[2] == a);
  assert(v.size() == 5);
  assert(v.capacity() == 8);
  v.resize(8);
  v[7] = b;
  assert(v[7] == b);
  assert(v.size() == v.capacity());
  my_vector::my_vector<int> vi(6);
  assert(vi.capacity() == 8);
  vi.resize(3);
  assert(vi.size() == 3);
  assert(vi.capacity() == 8);

  my_vector::my_vector<int> z(10);
  z.resize(3);
}

template <typename T>
void test_copy_constructor(T a,T b){
  my_vector::my_vector<T> v1;
  v1.push_back(a);
  v1.push_back(b);
  my_vector::my_vector<T> v2 = v1;
  assert(v1[0] == v2[0]);
  assert(v1[1] == v2[1]);
  for (size_t i = 0; i < 10; i++){
    v2.push_back(i % 2 ? a : b);
  }
  my_vector::my_vector<T> v3 = v2;
  for (size_t i = 0; i < 12; i++){
    assert(v2[i] == v3[i]);
  }
}

template <typename T>
void test_eq(T a, T b){
  my_vector::my_vector<T> v1;
  my_vector::my_vector<T> v2;

  v1.push_back(a);
  v2 = v1;
  assert(v1[0] == v2[0]);
  v2.pop_back();
  v2.push_back(b);
  v1 = v2;
  assert(v1[0] == v2[0]);
  for (size_t i = 0; i < 100; i++){
    v1.push_back(a);
    v1.push_back(b);
  }
  v2 = v1;
  for (size_t i = 0; i < 201; i++){
    assert(v1[i] == v2[i]);
  } 
}

template <typename T>
void test_get_size(T a, T b){
  my_vector::my_vector<T> v;
  for (size_t i = 0; i < 10; i++){
    v.push_back(a);
    v.push_back(b);
  }
  assert(v.size() == 20);
  for (size_t i = 0; i < 10; i++){
    v.pop_back();
  }
  assert(v.size() == 10);
  for (size_t i = 0; i < 10; i++){
    v.pop_back();
  }
  assert(v.size() == 0);
}

template <typename T>
void test_puch_back(T a, T b){
  my_vector::my_vector<T> v;
  for (size_t i = 0; i < 100; i++){
    v.push_back(a);
    assert(v[i] == a);
    v.push_back(b);
    assert(v[++i] == b);
  }
}

template <typename T>
void test_pop_back(T a, T b){
  my_vector::my_vector<T> v;
  v.push_back(a);
  v.pop_back();
  assert(v.size() == 0);
  v.push_back(b);
  v.push_back(a);
  v.pop_back();
  assert(v[v.size() - 1] == b);
}

template <typename T>
void test_get_capacity(T a,T b){
  my_vector::my_vector<T> v;
  v.push_back(a);
  assert(v.capacity() == 1);
  v.push_back(b);
  assert(v.capacity() == 2);
  v.push_back(a);
  assert(v.capacity() == 4);
  for (size_t i = 0; i < 5; i++){
    v.push_back(a);
  }
  assert(v.capacity() == 8);
  v.push_back(b);
  assert(v.capacity() == 16);
}

template <typename T>
void test_is_empty(T a){
  my_vector::my_vector<T> v;
  assert(v.empty() == 1);
  v.push_back(a);
  assert(v.empty() == 0);
  v.pop_back();
  assert(v.empty() == 1);
}

template <typename T>
void test_reserve(){
  my_vector::my_vector<T> v;
  v.reserve(64);
  assert(v.capacity() == 64);
  v.reserve(1);
  assert(v.capacity() == 64);
  v.reserve(65);
  assert(v.capacity() == 64 * 2);
}

template<typename T>
void test_get_elem(T a, T b){
  my_vector::my_vector<T> v;
  v.push_back(a);
  assert(v[0] == a);
  v.push_back(b);
  assert(v[0] == a and v[1] == b);
}

template <typename T>
void test_clear(T a){
  my_vector::my_vector<T> v;
  for (size_t i = 0; i < 100; i++){
    v.push_back(a);
  }
  size_t capacity = v.capacity();
  v.clear();
  assert(v.size() == 0 and capacity == v.capacity());
}

template<typename T>
void test_move(T a, T b){
  my_vector::my_vector<int> v1, v2;
  v2.push_back(a);
  v2.push_back(b);
  v1 = std::move(v2);
  assert(v1[0] == a);
  assert(v1[1] == b);
}

template<typename T>
void test_my_vector(T a, T b){
  test_copy_constructor<T>(a, b);
  test_eq<T>(a, b);
  test_puch_back<T>(a, b);
  test_pop_back<T>(a, b);
  test_get_size<T>(a, b);
  test_get_capacity<T>(a, b);
  test_is_empty<T>(a);
  test_reserve<T>();
  test_get_elem<T>(a, b);
  test_clear<T>(a);
}

template<typename T>
void test_my_vector_default_constructible(T a, T b){
  test_default_constructor<T>();
  test_resize<T>(a, b);
  test_move<T>(a, b);
}


} // NAMESPACE tests ENDS



int main() {
  test::test_my_vector_default_constructible<int>(5, 10);
  test::test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
  my_vector::my_vector<int> v1, v2;
  v2 = std::move(v1);
}