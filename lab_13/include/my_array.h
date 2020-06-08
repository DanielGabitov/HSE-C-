#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <exception>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <string.h>
#include <limits.h>

namespace lab_13 {

template<typename T, size_t N>
class my_array {
public:
    T& at(size_t index);
    T& operator[](size_t index);
    const T& at(size_t index) const;
    const T& operator[](size_t index) const;

    constexpr bool empty() const;
    constexpr size_t size() const;
    void fill(T val);
private:
    T data_[N];
};

template<typename T, size_t N>
T& my_array<T, N>::at(size_t index){
    if (index >= N){
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T, size_t N>
const T& my_array<T, N>::at(size_t index) const {
    if (index >= N){
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T, size_t N>
T& my_array<T, N>::operator[](size_t index){
    return data_[index];
}

template<typename T, size_t N>
const T& my_array<T, N>::operator[](size_t index) const{
    return data_[index];
}

template<typename T, size_t N>
constexpr bool my_array<T, N>::empty() const{
    return false;
}

template<typename T, size_t N>
constexpr size_t my_array<T, N>::size() const{
    return N;
}

template<typename T, size_t N>
void my_array<T, N>::fill(T val){
    for (T &elem : data_){
        elem = val;
    }
}

template<size_t N>
class my_array<bool, N>{        // Необьявленные конструкторы и op= - default 
private:
    //
    class Proxy{
    public:
        Proxy(size_t offset, char *data);
        Proxy& operator=(bool value);
        Proxy& operator=(Proxy &other);
        operator bool() const;
    private:
        char *byte_;
        size_t offset_;
    };
    //
    char data_[(N  + CHAR_BIT - 1) / CHAR_BIT];
public:
    bool at(std::size_t index) const;
    bool operator[](std::size_t index) const;
    Proxy at(std::size_t index);
    Proxy operator[](std::size_t index);
    void fill(bool value);
    constexpr bool empty() const;
    constexpr size_t size() const; 
};

template<size_t N>
my_array<bool, N>::Proxy::Proxy(size_t offset, char *data)
    : byte_(data + offset / CHAR_BIT)
    , offset_(offset % CHAR_BIT)
    {}

template<size_t N>
my_array<bool, N>::Proxy::operator bool() const{
    return (*byte_ & (1 << offset_)) != 0;
}

template<size_t N>
typename my_array<bool, N>::Proxy& my_array<bool, N>::Proxy::operator=(bool other){
    *byte_ &= ~(1 << offset_);
    *byte_ |= ((int)other << offset_);
    return *this;
}

template<size_t N>
typename my_array<bool, N>::Proxy& my_array<bool, N>::Proxy::operator=(Proxy& other){
    *this = bool(other);
    return *this;
}

template<size_t N>
typename my_array<bool, N>::Proxy my_array<bool, N>::operator[](size_t index){
    return Proxy(index, data_);
}

template<size_t N>
bool my_array<bool, N>::operator[](size_t index) const{
    return data_[index];
}

template<size_t N>
bool my_array<bool, N>::at(size_t index) const{
    if (index >= N){
        throw std::out_of_range("Index out of range!");
    }
    return (*this)[index];
}

template<size_t N>
typename my_array<bool, N>::Proxy my_array<bool, N>::at(size_t index){
    if (index >= N){
        throw std::out_of_range("Index out of range!");
    }
    return (*this)[index];
}

template<size_t N>
constexpr size_t my_array<bool, N>::size() const {
    return N;
}

template<size_t N>
constexpr bool my_array<bool, N>::empty() const {
    return false;
}

template<size_t N>
void my_array<bool, N>::fill(bool value){
    int value_to_fill = (value == true) ? (~0) : 0;    // it works.
    memset(data_, value_to_fill, (N  + CHAR_BIT - 1) / CHAR_BIT);
}
}  // namespace lab_13

#endif  // MY_ARRAY_H_