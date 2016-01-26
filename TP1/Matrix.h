#ifndef _MATRIX_H_
#define _MATRIX_H_

class Matrix
{
public:
    Matrix(int size);
    Matrix(Matrix& m,int size, int start);
    Matrix(Matrix& c11, Matrix& c12, Matrix& c21, Matrix& c22);
    ~Matrix();

    static Matrix conventionalMultiplication(Matrix& l,Matrix& m);
    static Matrix strassenMultiplication(Matrix& l, Matrix& r);
    Matrix operator+(const Matrix& m);
    Matrix operator-(const Matrix& m);
private:
    int m_size;
    int m_memoryLineSize;
    bool m_ownMemory;
    int* m_data;
    static int m_leafSize;
};

#endif // _MATRIX_H_
