#include <matrix.h>

Matrix::Matrix()
    : _row_size(0)
    , _col_size(0)
    , _arr(nullptr)
{}

Matrix::Matrix(size_t row_size, size_t col_size)
    : _row_size(row_size)
    , _col_size(col_size)
    , _arr(nullptr){

    try{
        _arr = new int* [_row_size + 1];
        for (size_t i = 0; i < _row_size; i++){
            _arr[i] = new int [col_size];
        }
    }
    catch (const std::bad_alloc &error){
        if (_arr == nullptr){
            throw MatrixException("Unable to allocate memory.");    
        }
        size_t i = 0;
        while (_arr[i] != nullptr){
            delete _arr[i++];
        }
        delete [] _arr;
        throw MatrixException("Unable to allocate memory.");
    }
}

Matrix::~Matrix(){
    for (size_t i = 0; i < _row_size; i++){
        delete [] _arr[i];
    }
    delete [] _arr;
}

int Matrix::unsafe_get_elem(size_t i, size_t j) const{
    return _arr[i][j]; 
}

int Matrix::get_elem(size_t i, size_t j) const{
    if (i < _row_size and j < _col_size){
        return unsafe_get_elem(i, j);
    }
    throw MatrixException("ACCESS: bad index.");
}

Matrix::Matrix(const Matrix& other)
    : Matrix(other._row_size, other._col_size){

    for (size_t i = 0; i < _row_size; i++){
        for (size_t j = 0; j < _col_size; j++){
            _arr[i][j] = other.get_elem(i, j);
        }
    }
}

Matrix& Matrix::operator= (Matrix other){
    std::swap(_row_size, other._row_size);
    std::swap(_col_size, other._col_size);
    std::swap(_arr, other._arr);
    return *this;
}

std::istream& operator>> (std::istream& is, Matrix& matrix){
    is.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        size_t row_size, col_size;
        is >> row_size >> col_size;
        Matrix new_matrix(row_size, col_size);
        for (size_t i = 0; i < row_size; i++){
            for (size_t j = 0; j < col_size; j++){
                is >> new_matrix._arr[i][j];
            }
        }
        matrix = new_matrix;
    }
    catch(const std::istream::failure &error){
        throw MatrixException("LOAD: invalid file format.");
    }
    return is;
}

std::ostream& operator<< (std::ostream& os, const Matrix& matrix){
    for (size_t i = 0; i < matrix._row_size; i++){
        for (size_t j = 0; j < matrix._col_size; j++){
            os << matrix.get_elem(i, j) << ' '; 
        }
        os << '\n';
    }
    return os;
}

Matrix Matrix::operator+ (const Matrix& other) const {
    if (_row_size != other._row_size or _col_size != other._col_size){
        throw MatrixException("ADD: dimensions do not match.");
    }
    Matrix new_matrix(_row_size, _col_size);
    for (size_t i = 0; i < _row_size; i++){
        for (size_t j = 0; j < _col_size; j++){
            new_matrix._arr[i][j] = unsafe_get_elem(i, j) + other.unsafe_get_elem(i, j);
        }
    }
    return new_matrix;
}

Matrix& Matrix::operator+= (const Matrix& other){
    return *this = (*this + other);
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (_col_size != other._row_size){
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
    Matrix new_matrix(_row_size, other._col_size);
    for (size_t i = 0; i < _row_size; i++){
        for (size_t j = 0; j < other._col_size; j++){
            new_matrix._arr[i][j] = 0;
            for (size_t k = 0; k < _col_size; k++){
                new_matrix._arr[i][j] += get_elem(i, k) * other.get_elem(k, j);
            }
        }
    }
    return new_matrix;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    *this = (*this) * (other);
    return *this;
}

MatrixException::MatrixException(std::string _error_message)
    : _error_message(_error_message)
    {}

const char* MatrixException::what() const noexcept{
    return _error_message.c_str();
}