#ifndef BIOINFORMATICS_UTILS_H
#define BIOINFORMATICS_UTILS_H

#include <cstdlib>
#include <cstring>

class utils {
public:
    template<typename T>
    static const T& max(const T& a, const T& b);
    template<typename T>
    static const T& min(const T& a, const T& b);
};

template<typename T>
const T &utils::max(const T &a, const T &b) {
    return a > b ? a : b;
}

template<typename T>
const T &utils::min(const T &a, const T &b) {
    return a < b ? a : b;
}

class alphabet {
public:
    virtual ~alphabet() { }
    virtual int to_ordinal_value(char c) const = 0;
    virtual char to_char(int ordinal_value) const = 0;
    virtual int size() const = 0;
};

class sequence {
public:
    sequence(const char* start, size_t length);
    sequence(const char* start);
    const char* get_start();
    char at(size_t index);
    size_t get_length();
private:
    const char* start_;
    size_t length_;
};

template<typename T>
class matrix {
public:
    matrix(ssize_t row_base, size_t row_count, ssize_t column_base, size_t column_count);
    matrix(const matrix<T>& other);
    ~matrix();
    matrix<T>& operator=(const matrix<T>& other);
    T& access(ssize_t row, ssize_t column);
    T access(ssize_t row, ssize_t column) const;
    void set_all(const T& data);
    size_t row_count() const;
    size_t column_count() const;
    ssize_t row_base() const;
    ssize_t row_limit() const;
    ssize_t column_base() const;
    ssize_t column_limit() const;

private:
    ssize_t row_base_;
    ssize_t column_base_;
    ssize_t row_count_;
    ssize_t column_count_;
    T* array_;
};

template<typename T>
class alphabet_matrix {
public:
    alphabet_matrix(const alphabet *alpha);
    alphabet_matrix(const alphabet_matrix<T>& other);
    ~alphabet_matrix();
    alphabet_matrix<T>& operator=(const alphabet_matrix<T>& other);
    T& access(char row, char column);
    T access(char row, char column) const;
    void set_all(const T& data);
    const alphabet* get_alphabet() const;
private:
    const alphabet* alphabet_;
    matrix<T>* matrix_;
};

#pragma region matrix

template<typename T>
matrix<T>::matrix(ssize_t row_base, size_t row_count, ssize_t column_base, size_t column_count) :
    row_base_(row_base),
    row_count_(row_count),
    column_base_(column_base),
    column_count_(column_count),
    array_(new T[row_count * column_count]) {
}

template<typename T>
matrix<T>::matrix(const matrix<T> &other) :
        matrix(other.row_base_, other.row_count_, other.column_base_, other.column_count_) {
    *this = other;
}

template<typename T>
matrix<T>::~matrix() {
    delete[] array_;
    array_ = nullptr;
}

template<typename T>
matrix<T> &matrix<T>::operator=(const matrix<T> &other) {
    if (this != &other) {
        if (row_count_ != other.row_count_ || column_count_ != other.column_count_) {
            delete[] array_;
            array_ = new T[other.row_count_ * other.column_count_];
        }
        row_base_ = other.row_base_;
        row_count_ = other.row_count_;
        column_base_ = other.column_base_;
        column_count_ = other.column_count_;

        size_t cell_count = row_count_ * column_count_;
        for (size_t i = 0; i < cell_count; ++i) {
            array_[i] = other.array_[i];
        }
    }
    return *this;
}

template<typename T>
T& matrix<T>::access(ssize_t row, ssize_t column) {
    return *(array_ + (row - row_base_) * column_count_ + (column - column_base_));
}

template<typename T>
T matrix<T>::access(ssize_t row, ssize_t column) const {
    return *(array_ + (row - row_base_) * column_count_ + (column - column_base_));
}

template<typename T>
void matrix<T>::set_all(const T &data) {
    size_t cell_count = row_count_ * column_count_;
    for (size_t i = 0; i < cell_count; ++i) {
        array_[i] = data;
    }
}

template<typename T>
size_t matrix<T>::row_count() const {
    return row_count_;
}

template<typename T>
size_t matrix<T>::column_count() const {
    return column_count_;
}

template<typename T>
ssize_t matrix<T>::row_base() const {
    return row_base_;
}

template<typename T>
ssize_t matrix<T>::row_limit() const {
    return row_base_ + row_count_;
}

template<typename T>
ssize_t matrix<T>::column_base() const {
    return column_base_;
}

template<typename T>
ssize_t matrix<T>::column_limit() const {
    return column_base_ + column_count_;
}

#pragma endregion

#pragma region alphabet_matrix

template<typename T>
alphabet_matrix<T>::alphabet_matrix(const alphabet *alpha) :
        alphabet_(alpha),
        matrix_(new matrix<T>(0, alpha->size(), 0, alpha->size())) {
}

template<typename T>
alphabet_matrix<T>::alphabet_matrix(const alphabet_matrix<T> &other) :
        alphabet_matrix(other.alphabet_) {
    *this = other;
}

template<typename T>
alphabet_matrix<T>::~alphabet_matrix() {
    alphabet_ = nullptr;
    delete matrix_;
    matrix_ = nullptr;
}

template<typename T>
alphabet_matrix<T> &alphabet_matrix<T>::operator=(const alphabet_matrix<T> &other) {
    if (this != &other) {
        alphabet_ = other.alphabet_;
        *matrix_ = *other.matrix_;
    }
    return *this;
}

template<typename T>
T &alphabet_matrix<T>::access(char row, char column) {
    return matrix_->access(alphabet_->to_ordinal_value(row), alphabet_->to_ordinal_value(column));
}

template<typename T>
T alphabet_matrix<T>::access(char row, char column) const {
    return matrix_->access(alphabet_->to_ordinal_value(row), alphabet_->to_ordinal_value(column));
}

template<typename T>
void alphabet_matrix<T>::set_all(const T &data) {
    matrix_->set_all(data);
}

template<typename T>
const alphabet *alphabet_matrix<T>::get_alphabet() const {
    return alphabet_;
}

#pragma endregion



#endif //BIOINFORMATICS_UTILS_H
