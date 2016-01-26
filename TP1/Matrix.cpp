#include "Matrix.h"

int Matrix::m_leafSize = 4;

Matrix::Matrix(int size)
    : m_size(size)
    , m_memoryLineSize(size)
    , m_ownMemory(true)
{
    m_data = new int[m_size*m_size];
}

Matrix::Matrix(Matrix& m, int size, int start)
    : m_size(size)
    , m_ownMemory(false)
    , m_memoryLineSize(m.m_size)
{
    m_data = m.m_data + start;
}

Matrix::Matrix(Matrix& c11, Matrix& c12, Matrix& c21, Matrix& c22)
    : m__size(c11.m_size * 2)
    , m_memoryLineSize(c11.m_size * 2)
    , m_ownMemory(true)
{
    m_data = new int[m__size * m_size];
    for (int i = 0; i < c11.m_size; ++i)
    {
        for (int j = 0; i < c11.m_leafSize; ++j)
        {
            m_data[i * m_memoryLineSize + j] = c11.m_data[i * c11.m_memoryLineSize + j];
        }
    }
    for (int i = 0; i < c12.m_size; ++i)
    {
        for (int j = 0; i < c12.m_leafSize; ++j)
        {
            m_data[i * m_memoryLineSize + j + c12.m_size] = c12.m_data[i * c12.m_memoryLineSize + j];
        }
    }
    for (int i = 0; i < c21.m_size; ++i)
    {
        for (int j = 0; i < c21.m_leafSize; ++j)
        {
            m_data[i * m_memoryLineSize + c21.m_size * m_memoryLineSize + j] = c21.m_data[i * c21.m_memoryLineSize + j];
        }
    }
    for (int i = 0; i < c22.m_size; ++i)
    {
        for (int j = 0; i < c22.m_leafSize; ++j)
        {
            m_data[i * m_memoryLineSize + c22.m_size * m_memoryLineSize + j + c22.m_size] = c22.m_data[i * c22.m_memoryLineSize + j];
        }
    }
}

Matrix::~Matrix()
{
    if (m_ownMemory)
    {
        delete[] m_data;
    }
}

Matrix Matrix::conventionalMultiplication(const Matrix& m)
{
    if (m.m_size == m_size)
    {
        Matrix result(m_size);
        for (int i = 0; i < m_size; ++i)
        {
            for (int j = 0; j < m_size; ++j)
            {
                for (int k = 0; k < m_size; ++k)
                {
                    result.m_data[i * m_memoryLineSize + j] += m_data[i * m_memoryLineSize + j + k] * m.m_data[i * m_memoryLineSize + j + k * m_memoryLineSize];
                }
            }
        }
        return result;
    }
    else
    {
        throw new std::invalid_argument();
    }
}

Matrix& Matrix::operator+(const Matrix& m)
{
    Matrix result(m_size);
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            result = m_data[i * m_memoryLineSize + j] + m.m_data[i*m_memoryLineSize + j];
        }
    }
    return result;
}

Matrix& Matrix::operator-(const Matrix& m)
{
    Matrix result(m_size);
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            result = m_data[i * m_memoryLineSize + j] - m.m_data[i*m_memoryLineSize + j];
        }
    }
    return result;
}

Matrix Matrix::strassenMultiplication(const Matrix& l, const Matrix& r)
{
    if (l.m_size == r.m_size && (l.m_size & (~l.m_size + 1)) == l.m_size)) //Check is m_size is power of 2
    {
        if (l.m_size == m_leafSize)
        {
            return conventionalMultiplication(r);
        }
        else
        {
            int newSize = l.m_size / 2;
            Matrix a11(this, newSize, 0);
            Matrix a12(this, newSize, newSize);
            Matrix a21(this, newSize, newSize * l.m_memoryLineSize);
            Matrix a22(this, newSize, newSize * l.m_memoryLineSize + newSize);
            Matrix b11(r, newSize, 0);
            Matrix b12(r, newSize, newSize);
            Matrix b21(r, newSize, newSize * l.m_memoryLineSize);
            Matrix b22(r, newSize, newSize * l.m_memoryLineSize + newSize);

            Matrix aTemp = a11 + a12;
            Matrix bTemp = b11 + b22;
            Matrix p1 = strassenMultiplication(aTemp, bTemp);
            
            aTemp = a21 + a22;
            Matrix p2 = strassenMultiplication(aTemp, bTemp);

            bTemp = b12 - b22;
            Matrix p3 = strassenMultiplication(aTemp, bTemp);

            bTemp = b21 - b11;
            Matrix p4 = strassenMultiplication(aTemp, bTemp);

            aTemp = a11 + a12;
            Matrix p5 = strassenMultiplication(aTemp, bTemp);

            aTemp = a21 - a11;
            Matrix p6 = strassenMultiplication(aTemp, bTemp);

            aTemp = a12 - a22;
            Matrix p7 = strassenMultiplication(aTemp, bTemp);

            Matrix c12 = p3 + p5;
            Matrix c21 = p2 + p4;
            aTemp = p1 + p4;
            bTemp = aTemp + p6;
            Matrix c11 = bTemp - p5;
            aTemp = p1 + p3;
            bTemp = aTemp + p6;
            Matrix c22 = bTemp - p2;

            return Matrix(c11, c12, c21, c22);
        }
    }
    else
    {
        throw new std::invalid_argument();
    }
}
