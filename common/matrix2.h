#ifndef MUSTARD_MATRIX2_H
#define MUSTARD_MATRIX2_H

#include <iosfwd>
#include <vector>
#include <algorithm>
#include <iostream>

namespace mustard {

namespace matrix {

template <typename T>
class common_matrix
{
private:

    int _row, _col;

    T * _data;

public:

    common_matrix(int row, int col, const T & t = T());

    ~common_matrix();

    common_matrix(const common_matrix<T> & m);

    common_matrix<T> & operator= (const common_matrix<T> & m);

    int row() const { return _row; }

    int col() const { return _col; }

    struct _matrix_row
    {
        int _row;

        common_matrix<T> & _mx;

        _matrix_row(int row, common_matrix<T> & mx);

        _matrix_row(const _matrix_row & r);

        T & operator[] (int col);

    private:
        _matrix_row & operator= (const _matrix_row & r);

    };

    struct _const_matrix_row
    {
        int _row;

        const common_matrix<T> & _mx;

        _const_matrix_row(int row, const common_matrix<T> & mx);

        _const_matrix_row(const _const_matrix_row & r);

        T operator[] (int col) const;

    private:
        _const_matrix_row & operator= (const _const_matrix_row & r);
    };

    _matrix_row operator[] (int row);

    _const_matrix_row operator[] (int row) const;

private:

    T & d(int r, int c);

    T d(int r, int c) const;

    void swap(common_matrix<T> & m);

};

template <typename T>
std::istream & operator>> (std::istream & in, common_matrix<T> & m);

template <typename T>
std::ostream & operator<< (std::ostream & out, const common_matrix<T> & m);

template <typename T>
common_matrix<T> * read_common_matrix();

template <typename T>
void print(const common_matrix<T> * m);

template <typename T>
void print(const common_matrix<T> & m);

template <typename T>
class sparse_matrix
{
public:

    struct tup
    {
        int r;
        int c;
        T   d;
        tup(int r = 0, int c = 0, const T & d = T())
            : r(r), c(c), d(d)
        {}
    };

private:

    std::vector<tup> _data;

    int _row, _col;

    static const T _default_value;

public:

    sparse_matrix(int row, int col);

    ~sparse_matrix();

    sparse_matrix(const sparse_matrix<T> & m);

    sparse_matrix<T> & operator= (const sparse_matrix<T> & m);

    int row() const { return _row; }

    int col() const { return _col; }

    int num_elements() const { return (int) _data.size(); }

    void get_elements(std::vector<tup> & elements) const;

    struct _elem_proxy
    {
        int _row, _col;

        sparse_matrix<T> & _mx;

        _elem_proxy(int row, int col, sparse_matrix<T> & mx);

        _elem_proxy(const _elem_proxy & e);

        _elem_proxy & operator =(const T & e);

        operator T() const;

    private:
        _elem_proxy & operator =(const _elem_proxy & e);
        
    };

    struct _matrix_row
    {
        int _row;

        sparse_matrix<T> & _mx;

        _matrix_row(int row, sparse_matrix<T> & mx);

        _matrix_row(const _matrix_row & r);

        _elem_proxy operator[] (int i);

    private:
        _matrix_row & operator= (const _matrix_row & r);
    };

    struct _const_matrix_row
    {
        int _row;

        const sparse_matrix<T> & _mx;

        _const_matrix_row(int row, const sparse_matrix<T> & mx);

        _const_matrix_row(const _const_matrix_row & r);

        T operator [](int i) const;

    private:
        _const_matrix_row & operator =(const _const_matrix_row & r);
    };

    _matrix_row operator [](int row);

    _const_matrix_row operator [](int row) const;

private:

    const tup * find(int row, int col) const;

    void set(int row, int col, const T & t);

    T get(int row, int col) const;

    void swap(sparse_matrix<T> & m);

};

template <typename T>
std::istream & operator >>(std::istream & in, sparse_matrix<T> & m);

template <typename T>
std::ostream & operator <<(std::ostream & out, const sparse_matrix<T> & m);

template <typename T>
sparse_matrix<T> * read_sparse_matrix();

template <typename T>
void print(const sparse_matrix<T> * m);

template <typename T>
void print(const sparse_matrix<T> & m);

template <typename T>
void print_as_common(const sparse_matrix<T> & m);

template <typename T>
void print_as_common(const sparse_matrix<T> * m);


template <typename T>
class symmetric_matrix
{
private:

    int _n;

    T * _data;

public:

    symmetric_matrix(int n, const T & t = T());

    ~symmetric_matrix();

    symmetric_matrix(const symmetric_matrix<T> & m);

    symmetric_matrix<T> & operator=(const symmetric_matrix<T> & m);

    int row() const { return _n; }

    int col() const { return _n; }

    struct _matrix_row
    {
        int _row;

        symmetric_matrix<T> & _mx;

        _matrix_row(int row, symmetric_matrix<T> & mx)
            : _row(row), _mx(mx)
        {}

        _matrix_row(const _matrix_row & r)
            : _row(r._row), _mx(r._mx)
        {}

        T & operator[](int col)
        {
            return _mx.d(_row, col);
        }

    private:
        _matrix_row & operator=(const _matrix_row & r);

    };

    struct _const_matrix_row
    {
        int _row;

        const symmetric_matrix<T> & _mx;

        _const_matrix_row(int row, const symmetric_matrix<T> & mx)
            : _row(row), _mx(mx)
        {}

        _const_matrix_row(const _const_matrix_row & r)
            : _row(r._row), _mx(r._mx)
        {}

        T operator[](int col) const
        {
            return _mx.d(_row, col);
        }

    private:
        _const_matrix_row & operator=(const _const_matrix_row & r);

    };

    _matrix_row operator[](int row)
    {
        return _matrix_row(row, *this);
    }

    _const_matrix_row operator[](int row) const
    {
        return _const_matrix_row(row, *this);
    }

private:

    T & d(int r, int c)
    {
        if (r < c) {
            int t = r;
            r = c;
            c = t;
        }
        return _data[r * (r + 1)/2 + c];
    }

    T d(int r, int c) const
    {
        return const_cast<symmetric_matrix<T>*>(this)->d(r,c);
    }

    void swap(symmetric_matrix<T> & m);

};


#include "impl/__common_matrix_impl.h"
#include "impl/__sparse_matrix_impl.h"
#include "impl/__symmetric_matrix.h"

} // namespace ::mustard::matrix

} // namespace ::mustard

#endif  // ifndef MUSTARD_MATRIX2_H

