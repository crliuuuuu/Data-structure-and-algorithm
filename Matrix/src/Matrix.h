/**
 * @file   Matrix.h
 * @author Liu chenruo <1816655804@qq.com>
 * @date   Sun Oct 3 23:37:14 2021
 *
 * @brief  Inplementation of Matrix and Vector template class.
 *
 */

#ifndef _lcrMatrix_
#define _lcrMartix_

#include <iostream>
#include <cstdlib>
#include <new>


template <typename T>
class Matrix;

template <typename T>
class RowVector;

template <typename T>
class ColVector;

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <typename T>
T operator*(const RowVector<T>& lhs, const ColVector<T>& rhs);

template <typename T>
T operator*(const ColVector<T>& lhs, const ColVector<T>& rhs);

template <typename T>
T operator*(const RowVector<T>& lhs, const RowVector<T>& rhs);



template <typename T>
class Matrix
{
 protected:
  int n_row ;
  int n_col ;
  T* matrix_elements;

  /**
   * Copy datas from Matrix to Matrix.
   */
  void copy_Mem(const T* _o, T* _n, int _s);
  
 public:
  Matrix()
  {
    matrix_elements = nullptr;
    n_row = 0;
    n_col = 0;
  }
  
  Matrix(int _r, int _c);
  
  Matrix(const Matrix<T>& rhs);
  
  ~Matrix();
  
  T& operator()(int _i, int _j) const;
  
  Matrix<T>& operator=(const Matrix<T>& rhs);

  /**
   * Is_square means the matrix is a square matrix.
   */
  bool is_square() const;

  friend
    Matrix<T> operator * <> (const Matrix<T>& lhs, const Matrix<T>& rhs);
};


template <typename T>
class RowVector: public Matrix<T>
{
 public:
  RowVector()
  {
    Matrix<T>::matrix_elements = nullptr;
    Matrix<T>::n_row = 1;
    Matrix<T>::n_col = 0;
  }
  
  RowVector(int _c);
  
  ~RowVector()
  {
    if (Matrix<T>::matrix_elements != nullptr)
      delete [] Matrix<T>::matrix_elements;
    Matrix<T>::matrix_elements = nullptr;
  }
  
  friend
    T operator * <> (const RowVector<T>& lhs, const ColVector<T>& rhs);
  friend
    T operator * <> (const RowVector<T>& lhs, const RowVector<T>& rhs);
};


template <typename T>
class ColVector: public Matrix<T>
{
 public:
  ColVector()
  {
    Matrix<T>::matrix_elements = nullptr;
    Matrix<T>::n_row = 0;
    Matrix<T>::n_col = 1;
  }
  
  ColVector(int _n);
  
  ~ColVector()
  {
    if (Matrix<T>::matrix_elements != nullptr)
      delete [] Matrix<T>::matrix_elements;
    Matrix<T>::matrix_elements = nullptr;
  }
  
  friend
    T operator * <> (const RowVector<T>& lhs, const ColVector<T>& rhs);
  friend
    T operator * <> (const ColVector<T>& lhs, const ColVector<T>& rhs);
};


/**
 * To stop the program abnormally.
 */
void abort(int _err) 
{
  switch (_err)
  {
  case 2:
    std::cout << "Invalid multiplication." << std::endl;
    break;
  case 3:
    std::cout << "Invalid inner product." << std::endl;
    break;
  default:
    break;
  }
  exit(-1);
}

template <typename T>
void Matrix<T>::copy_Mem(const T* _o, T* _n, int _s)
{
  for(int i = 0; i < _s; i++)
    _n[i] = _o[i];
}

template <typename T>
Matrix<T>::Matrix(int _r, int _c)
{
  matrix_elements = new T [_r * _c];
  n_row = _r;
  n_col = _c;
}

template <typename T>
RowVector<T>::RowVector(int _c)
{
  Matrix<T>::matrix_elements = new T [_c];
  Matrix<T>::n_row = 1;
  Matrix<T>::n_col = _c;
}

template <typename T>
ColVector<T>::ColVector(int _n)
{
  Matrix<T>::matrix_elements = new T [_n];
  Matrix<T>::n_row = _n;
  Matrix<T>::n_col = 1;
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
{
  n_row = rhs.n_row;
  n_col = rhs.n_col;
  if (matrix_elements != nullptr)
    delete [] matrix_elements;
  matrix_elements = new T [n_row * n_col];
  copy_Mem(rhs.matrix_elements, matrix_elements, n_row * n_col);
}

template <typename T>
Matrix<T>::~Matrix()
{
  if (matrix_elements != nullptr)
    delete [] matrix_elements;
  matrix_elements = nullptr;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
  if (matrix_elements != nullptr)
    delete [] matrix_elements;
  n_row = rhs.n_row;
  n_col = rhs.n_col;
  matrix_elements = new T [n_row * n_col];
  copy_Mem(rhs.matrix_elements, matrix_elements, n_row * n_col);
  return *this;
}

template <typename T>
T& Matrix<T>::operator()(int _i, int _j) const
{
  /// Quit the program if index of Matrix is out of range.
  if (_i < 0 || _i > n_row - 1 || _j < 0 || _j > n_col - 1)
  {
    std::cout << "Out of range." << std::endl;
    exit(-1);
  }
  return *(matrix_elements + n_col * _i + _j);
}

template <typename T>
bool Matrix<T>::is_square() const
{
  if (n_col == n_row)
    return true;
  else
    return false;
}


/**
 * Inplementation of matrix multiplication.
 */
template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs,const Matrix<T>& rhs)
{
  if (lhs.n_col != rhs.n_row)
    abort(2);
  Matrix<T> A(lhs.n_row, rhs.n_col);
  for (int i = 0; i < A.n_row; i++)
  {
    for (int j = 0; j < A.n_col; j++)
    {
      A(i, j) = T();
      for (int k = 0; k < lhs.n_col; k++)
	A(i, j) += lhs(i, k) * rhs(k, j);
    }
  }
  return A;
}

template <typename T>
T operator*(const RowVector<T>& lhs, const ColVector<T>& rhs)
{
  if (lhs.n_col != rhs.n_row)
    abort(3);
  T sum = T();
  for (int i = 0; i < lhs.n_col; i++)
    sum += lhs(0, i) * rhs(i, 0);
  return sum;
}

/**
 * Inplementation of ColVector inner product.
 */
template <typename T>
T operator*(const ColVector<T>& lhs, const ColVector<T>& rhs)
{
  if (lhs.n_row != rhs.n_row)
    abort(3);
  T sum = T();
  for (int i = 0; i < lhs.n_row; i++)
    sum += lhs(i, 0) * rhs(i, 0);
  return sum;
}

/**
 * Inplementation of RowVector inner product.
 */
template <typename T>
T operator*(const RowVector<T>& lhs, const RowVector<T>& rhs)
{
  if (lhs.n_col != rhs.n_col)
    abort(3);
  T sum = T();
  for (int i = 0; i < lhs.n_col; i++)
    sum += lhs(0, i) * rhs(0, i);
  return sum;
}


#else
/// Do Nothing.
#endif
