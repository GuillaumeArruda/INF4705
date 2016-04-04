#ifndef _MATRIX_H_
#define _MATRIX_H_

class Matrix
{
public:
    Matrix(int size);
    Matrix(int size, int* data);
    Matrix(const Matrix& m);
    Matrix(const Matrix& m,int size, int start);
    Matrix(const Matrix& c11,const Matrix& c12,const Matrix& c21,const Matrix& c22);
    Matrix(Matrix&& moved);
    ~Matrix();

    void print();
    static Matrix conventionalMultiplication(const Matrix& l,const Matrix& m);
    static Matrix strassenMultiplication(const Matrix& l,const Matrix& r);
    Matrix operator+(const Matrix& m);
    Matrix operator-(const Matrix& m);
    bool operator==(const Matrix& m);
    static void setLeafSize(int leafSize);
private:
    int m_size;
    int* m_data;
    static int m_leafSize;
};
#endif // _MATRIX_H_
