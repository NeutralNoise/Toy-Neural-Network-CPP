#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <vector>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <vector>

class Matrix {

public:

  Matrix() {

  }

  Matrix(const int &rows, const int &cols) {
    m_cols = cols;
    m_rows = rows;
    m_data.resize(rows * cols);

    for(size_t i = 0; i < m_data.size(); i++) {
      m_data[i] = 0.0f;
    }
  }

  static Matrix FromArray(const std::vector<float> &arr) {
    return Matrix(arr.size(), 1).map([=](float val, int i,int j)->float{
      return arr[i];
    });

  }

  static Matrix Subtract(const Matrix &a, const Matrix &b) {
    if(a.GetRows() != b.GetRows() || a.GetCols() != b.GetCols()) {
      std::cout << "Subtract.\n";
      std::cout << "Columns and Rows of A must match Columns and Rows of B.\n";
      return Matrix(0,0);
    }

    Matrix rtn(a.GetRows(), a.GetCols());

    return rtn.map([&](float val, int i,int j)->float{
      return a.GetValue(i,j) - b.GetValue(i,j);});
  }

  std::vector<float> ToArray() {
    std::vector<float> rtn;
    for(size_t i = 0; i < m_rows; i++) {
      for(size_t j = 0; j < m_cols; j++) {
	rtn.push_back(m_data[j + i * m_cols]);
      }
    }
    return rtn;

  }

  void Randomize(){
    float a = 0.0f;
    float b = 1.0f;

    this->map([=](float val, int i, int j)->float{
    int rnum1 = rand();
    int rnum2 = rand();
    int randnum = (((rnum1 + rnum2)*(rnum1 + rnum2 + 1) / 2) + rnum2) % RAND_MAX;
    //float random = ((float) rand()) / (float) RAND_MAX;
    float random = ((float) randnum) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;

    });

  }

  Matrix add(const float &val) {
    return Matrix(this->m_rows, this->m_cols).map([=](float val, int i, int j)->float{
      return this->m_data[j +i * m_cols] + val;});
  }

  Matrix operator+(const Matrix &other) {
    if(this->GetRows() != other.GetRows() || this->GetCols() != other.GetCols()) {
      std::cout << "Add. Operator\n";
      std::cout << "Columns and Rows of A must match Columns and Rows of B.\n";
      return Matrix(0,0);
    }
    return Matrix(this->m_rows, this->m_cols).map([=](float val, int i, int j)->float{
      return this->m_data[j + i * m_cols] + other.GetValue(i,j);});
  }

  static Matrix Transpose(const Matrix &mat) {
    return Matrix(mat.GetCols(), mat.GetRows()).map([=](float val, int i, int j)->float{
      return mat.GetValue(j,i);});
  }

  static Matrix Multiply(const Matrix &a, const Matrix &b) {
     if(a.GetCols() != b.GetRows()) {
       std::cout << "Multiply Static.\n";
      std::cout << "Columns of A must match rows of B..\n";
      return Matrix(0,0);
    }

    return Matrix(a.GetRows(), b.GetCols()).map([=](float val, int i, int j)->float{
      float sum = 0.0f;
      for (int k = 0; k < a.GetCols(); k++) {
          sum += a.GetValue(i,k) * b.GetValue(k,j);
        }
        return sum;
    });

  }

  Matrix operator*(const Matrix &other) {
      if(this->GetCols() != other.GetCols() || this->GetRows() != other.GetRows()) {
	std::cout << "Multiply. Operator \n";
	std::cout << "Columns of A must match rows of B..\n";
	return Matrix(0,0);
      }
     return Matrix(other.GetRows(), this->GetCols()).map([=](float val, int i, int j)->float{
      float sum = 0.0f;
      for (int k = 0; k < this->GetCols(); k++) {
          sum += this->GetValue(i,k) * other.GetValue(k,j);
        }
        return sum;
     });
  }


  Matrix Multiply(const float &num) {
    return this->map([=](float val, int i, int j)->float{
       return this->GetValue(i,j) * num;
    });
  }

  Matrix map(std::function<float(const float&, const int&, const int&)> func) {
    for(size_t i = 0; i < m_rows; i++) {
      for(size_t j = 0; j < m_cols; j++) {
	float val = m_data[j + i * m_cols];
	m_data[j + i * m_cols] = func(val, i, j);
      }
    }
    return *this;
  }

  static Matrix map(const Matrix &mat, std::function<float(const float&, const int&, const int&)> func) {
    Matrix rtn(mat.GetRows(), mat.GetCols());
    rtn = mat;
    return rtn.map(func);
  }


  int GetRows() const {
    return m_rows;
  }

  int GetCols() const {
    return m_cols;
  }

  float GetValue(const int &row, const int &col) const {
    return m_data[col + row * m_cols];
  }

  size_t GetSize() const {
    return m_cols * m_rows;
  }

  void Display() {
    this->map([=](float val, int i, int j)->float{
      std::cout << val;
      if(j == m_cols - 1) {
	std::cout << "\n";
      }
      return val;
    });
  }

private:

  int m_cols;
  int m_rows;

  std::vector<float> m_data;

};

#endif //MATRIX_H_INCLUDED
