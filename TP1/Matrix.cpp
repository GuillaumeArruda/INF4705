#include "Matrix.h"
#include <stdexcept>
#include <iostream>

int Matrix::m_leafSize = 1;

Matrix::Matrix(int size)
    : m_size(size)
    , m_memoryLineSize(size)
    , m_ownMemory(true)
{
    m_data = new int[m_size*m_size];
}

Matrix::Matrix(const Matrix& m)
    : m_size(m.m_size)
    , m_memoryLineSize(m.m_size)
    , m_ownMemory(true)
{
    m_data = new int[m_size * m_size];
    for(int i = 0; i < m_size * m_size; ++i)
    {
        m_data[i] = m.m_data[i];
    }
}

Matrix::Matrix(Matrix& m, int size, int start)
    : m_size(size)
    , m_memoryLineSize(m.m_memoryLineSize)
    , m_ownMemory(false)
{
    m_data = m.m_data + start;
}

void Matrix::setData(int* data, int size)
{
    if(m_size < size)
    {
        delete[] m_data;
        m_size = size;
        m_data = new int[m_size * m_size];
    }
    for(int i = 0; i < size * size; ++i)
    {
        m_data[i] = data[i];
    }
}

Matrix::Matrix(Matrix& c11, Matrix& c12, Matrix& c21, Matrix& c22)
    : m_size(c11.m_size * 2)
    , m_memoryLineSize(c11.m_size * 2)
    , m_ownMemory(true)
{
    m_data = new int[m_size * m_size];
    for (int i = 0; i < c11.m_size; ++i)
    {
        for (int j = 0; j < c11.m_size; ++j)
        {
            m_data[i * m_memoryLineSize + j] = c11.m_data[i * c11.m_memoryLineSize + j];
        }
    }
    for (int i = 0; i < c12.m_size; ++i)
    {
        for (int j = 0; j < c12.m_size; ++j)
        {
            m_data[i * m_memoryLineSize + j + c12.m_size] = c12.m_data[i * c12.m_memoryLineSize + j];
        }
    }
    for (int i = 0; i < c21.m_size; ++i)
    {
        for (int j = 0; j < c21.m_size; ++j)
        {
            m_data[i * m_memoryLineSize + c21.m_size * m_memoryLineSize + j] = c21.m_data[i * c21.m_memoryLineSize + j];
        }
    }
    for (int i = 0; i < c22.m_size; ++i)
    {
        for (int j = 0; j < c22.m_size; ++j)
        {
            m_data[i * m_memoryLineSize + c22.m_size * m_memoryLineSize + j + c22.m_size] = c22.m_data[i * c22.m_memoryLineSize + j];
        }
    }
}

Matrix::~Matrix()
{
    if (m_ownMemory)
    {
        //delete[] m_data;
    }
}

Matrix Matrix::conventionalMultiplication(Matrix& l, Matrix& m)
{
    if (m.m_size == l.m_size)
    {
        Matrix result(l.m_size);
        for (int i = 0; i < l.m_size; ++i)
        {
            for (int j = 0; j < l.m_size; ++j)
            {
                for (int k = 0; k < l.m_size; ++k)
                {
                    result.m_data[i * l.m_memoryLineSize + j] += l.m_data[k * l.m_memoryLineSize + j] * m.m_data[i * m.m_memoryLineSize + k];
                }
            }
        }
        return result;
    }
    else
    {
        throw new std::invalid_argument("");
    }
}

Matrix Matrix::operator+(const Matrix& m)
{
    Matrix result(m_size);
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            result.m_data[i * result.m_memoryLineSize + j] = m_data[i * m_memoryLineSize + j] + m.m_data[i*m_memoryLineSize + j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& m)
{
    Matrix result(m_size);
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            result.m_data[i * result.m_memoryLineSize + j] = m_data[i * m_memoryLineSize + j] - m.m_data[i*m_memoryLineSize + j];
        }
    }
    return result;
}

Matrix Matrix::strassenMultiplication(Matrix& l, Matrix& r)
{
    if (l.m_size == r.m_size && (l.m_size & (~l.m_size + 1)) == l.m_size) //Check is m_size is power of 2
    {
        if (l.m_size == m_leafSize)
        {
            return conventionalMultiplication(l,r);
        }
        else
        {
            int newSize = l.m_size / 2;
            Matrix a11(l, newSize, 0);
            Matrix a12(l, newSize, newSize);
            Matrix a21(l, newSize, newSize * l.m_memoryLineSize);
            Matrix a22(l, newSize, newSize * l.m_memoryLineSize + newSize);
            Matrix b11(r, newSize, 0);
            Matrix b12(r, newSize, newSize);
            Matrix b21(r, newSize, newSize * r.m_memoryLineSize);
            Matrix b22(r, newSize, newSize * r.m_memoryLineSize + newSize);

            Matrix aTemp = a11 + a22;
            Matrix bTemp = b11 + b22;
            Matrix m1 = strassenMultiplication(aTemp, bTemp); // (a11 + a22) x (b11 + b22)
            aTemp = a21 + a22;
            Matrix m2 = strassenMultiplication(aTemp, b11); // (a11 + a22) x b11
            bTemp = b12 - b22;
            Matrix m3 = strassenMultiplication(a11, bTemp); // a11 x (b12 - b22)
            bTemp = b21 - b11;
            Matrix m4 = strassenMultiplication(a22, bTemp); //a22 x (b21 - b11)
            aTemp = a11 + a12;
            Matrix m5 = strassenMultiplication(aTemp, b22); //(a11 + a12) x b22
            aTemp = a21 - a11;
            bTemp = b11 +b12;
            Matrix m6 = strassenMultiplication(aTemp, bTemp); //(a21 - a11) x (b11 + b12)
            aTemp = a12 - a22;
            bTemp = b21 + b22;
            Matrix m7 = strassenMultiplication(aTemp, bTemp); //(a12 - a22) x (b21 + b22)

            Matrix c12 = m3 + m5; // m3 + m5
            Matrix c21 = m2 + m4; // m2 + m4
            aTemp = m1 + m4;
            bTemp = aTemp + m7;
            Matrix c11 = bTemp - m5; // m1 + m4 - m5 + m7
            aTemp = m1 + m3;
            bTemp = aTemp + m6;
            Matrix c22 = bTemp - m2; // m1 - m2 + m3 + m6

            return Matrix(c11, c12, c21, c22);
        }
    }
    else
    {
        throw new std::invalid_argument("");
    }
}

void Matrix::print()
{
    for(int i = 0; i < m_size; ++i)
    {
        for(int j = 0; j < m_size; ++j)
        {
            std::cout << m_data[i * m_memoryLineSize + j] << ' ';
        }
        std::cout << std::endl;
    }
}
