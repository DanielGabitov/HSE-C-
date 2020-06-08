#include <exception>
#include <string>
#include <fstream>

class Matrix{
private:
    size_t _row_size;
    size_t _col_size;
    int **_arr;
    int unsafe_get_elem(size_t, size_t) const;
public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix (const Matrix&);
    ~Matrix();
    Matrix& operator= (Matrix);
    Matrix operator+ (const Matrix&) const;
    Matrix operator* (const Matrix&) const;
    Matrix& operator+= (const Matrix&);
    Matrix& operator*= (const Matrix&);
    int get_elem(size_t, size_t) const;
    friend std::istream& operator>> (std::istream&, Matrix&);
    friend std::ostream& operator<< (std::ostream&, const Matrix&);
};

class MatrixException: public std::exception {
private:
    std::string _error_message;
public:
    MatrixException(std::string);
    virtual const char * what() const noexcept override;
};