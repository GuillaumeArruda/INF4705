#include "Matrix.h"

int main()
{
    int data[]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Matrix m(4);
    Matrix t(4);
    m.setData(data, 4);
    t.setData(data, 4);
    Matrix d = Matrix::strassenMultiplication(m,t);
    d.print();
}

