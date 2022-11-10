// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0 || sz > MAX_VECTOR_SIZE) throw out_of_range("TDynamicVector::TDynamicVector(size_t size = 1)");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    if (sz <= 0 || sz > MAX_VECTOR_SIZE) throw out_of_range("TDynamicVector::TDynamicVector(T* arr, size_t s)");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(new T[v.sz])
  {
      std::copy(v.pMem, v.pMem + v.sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept :sz(0), pMem(nullptr)
  {
      swap(*this,v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  const TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz; 
          pMem = new T[v.sz];
          std::copy(v.pMem, v.pMem + v.sz, pMem);
      }
      return *this;
  }
  const TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete [] pMem;
          pMem = nullptr;
          sz = 0;
          swap(*this, v);
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz || ind < 0 ) throw std::out_of_range("T& TDynamicVector::at(size_t ind");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind < 0 ) throw std::out_of_range("const T& TDynamicVector::at(size_t ind const");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz == v.sz) {
          for (size_t i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) return false;
          }
          return true;
      }
      return false;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (size_t i = 0; i < tmp.sz; i++) {
          tmp.pMem[i] = tmp.pMem[i] + val;
      }
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (size_t i = 0; i < tmp.sz; i++) {
          tmp.pMem[i] = tmp.pMem[i] - val;
      }
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (size_t i = 0; i < tmp.sz; i++) {
          tmp.pMem[i] = tmp.pMem[i] * val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw std::length_error("TDynamicVector operator+(const TDynamicVector& v)");
      TDynamicVector<T> tmp(*this);
      for (size_t i = 0; i < tmp.sz; i++) {
          tmp.pMem[i] = tmp.pMem[i] + v.pMem[i];
      }
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz ) throw std::length_error("TDynamicVector operator-(const TDynamicVector& v)");
      TDynamicVector<T> tmp(*this);
      for (size_t i = 0; i < tmp.sz; i++) {
          tmp.pMem[i] = tmp.pMem[i] - v.pMem[i];
      }
      return tmp;

  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw std::length_error("T operator*(const TDynamicVector& v)");
      T tmp = T();
      for (size_t i = 0; i < sz; i++) {
          tmp += pMem[i] * v.pMem[i];
      }
      return tmp;

  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    ostr << std::endl;
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' ';// требуется оператор<< для типа T
    ostr << std::endl;
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix<T>(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE) throw std::out_of_range("TDynamicMaxtrix::TDynamicMatrix(size_t s = 1)");
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    using TDynamicVector<TDynamicVector<T>>::size;
    
    using TDynamicVector<TDynamicVector<T>>::operator[];

    T& at(size_t row, size_t col)
    {
        if (row < 0 || col < 0) throw std::invalid_argument("T& at(size_t row,size_t col)");
        if (row >= sz || col >= sz) throw std::out_of_range("T& at(size_t row,size_t col)");
        return pMem[row][col];
    }

    const T& at(size_t row,size_t col) const 
    {
        if (row < 0 || col < 0 ) throw std::invalid_argument("const T& at(size_t row,size_t col) const");
        if (row >= sz || col >= sz) throw std::out_of_range("const T& at(size_t row,size_t col) const");
        return pMem[row][col];
    }

    // Транспонирование матрицы
    TDynamicMatrix trans()
    {
        TDynamicMatrix<T> tmp(*this);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = i + 1; j < sz; j++) {
                std::swap(tmp[i][j], tmp[j][i]);
            }
        }
        return tmp;
    }
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T val)
  {
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      //if (sz != v.size) throw std::length_error("TDynamicVector<T> TDynamicMatrix::operator*(const TDynamicVector<T>& v)");
      TDynamicVector<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp[i] = pMem[i] * v;
      }
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (size() != m.size()) throw std::length_error("TDynamicMatrix TDynamicMatrix::operator+(const TDynamicMatrix& m)");
      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp[i] = pMem[i] + m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (size() != m.size()) throw std::length_error("TDynamicMatrix TDynamicMatrix::operator-(const TDynamicMatrix& m)");
      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp[i] = pMem[i] - m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (size() != m.size()) throw std::length_error("TDynamicMatrix TDynamicMatrix::operator*(const TDynamicMatrix& m)");
      TDynamicMatrix<T> tmp1(sz);
      TDynamicMatrix<T> tmp2(m);
      tmp2 = tmp2.trans();
      for (size_t i = 0; i < sz; i++) {
          tmp1[i] = *this * tmp2[i];
      }
      return tmp1.trans();
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.size(); i++)
          istr >> v.pMem[i]; 
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.size(); i++)
          ostr << v.pMem[i] << ' '; 
      return ostr;
  }
};

#endif
