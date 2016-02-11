#include "Matrix.h"
#include <stdexcept>
#include <iostream>

int Matrix::m_leafSize = 32;

Matrix::Matrix(int size)
    : m_size(size)
{
    m_data = new int[m_size*m_size];
    for(int i = 0; i < m_size * m_size; ++i)
    {
        m_data[i] = 0;
    }
}

Matrix::Matrix(int size, int* data)
    : m_size(size)
{
    m_data = new int[m_size * m_size];
    for(int i = 0; i < size * size; ++i)
    {
        m_data[i] = data[i];
    }
}

Matrix::Matrix(const Matrix& m)
    : m_size(m.m_size)
{
    m_data = new int[m_size * m_size];
    for(int i = 0; i < m_size * m_size; ++i)
    {
        m_data[i] = m.m_data[i];
    }
}

Matrix::Matrix(const Matrix& m, int size, int start)
    : m_size(size)
{
    //m_data = m.m_data + start;
    m_data  = new int[m_size * m_size];
    for(int i = 0; i < m_size; ++i)
    {
        for(int j = 0; j < m_size; ++j)
        {
            m_data[i * m_size + j] = m.m_data[i * m.m_size + start + j];
        }
    }
}

Matrix::Matrix(const Matrix& c11,const Matrix& c12,const Matrix& c21,const Matrix& c22)
    : m_size(c11.m_size * 2)
{
    m_data = new int[m_size * m_size];
    for (int i = 0; i < c11.m_size; ++i)
    {
        for (int j = 0; j < c11.m_size; ++j)
        {
            m_data[i * m_size + j] = c11.m_data[i * c11.m_size + j];
        }
    }
    for (int i = 0; i < c12.m_size; ++i)
    {
        for (int j = 0; j < c12.m_size; ++j)
        {
            m_data[i * m_size + j + c12.m_size] = c12.m_data[i * c12.m_size + j];
        }
    }
    for (int i = 0; i < c21.m_size; ++i)
    {
        for (int j = 0; j < c21.m_size; ++j)
        {
            m_data[i * m_size + c21.m_size * m_size + j] = c21.m_data[i * c21.m_size + j];
        }
    }
    for (int i = 0; i < c22.m_size; ++i)
    {
        for (int j = 0; j < c22.m_size; ++j)
        {
            m_data[i * m_size + c22.m_size * m_size + j + c22.m_size] = c22.m_data[i * c22.m_size + j];
        }
    }
}

Matrix::~Matrix()
{
    delete[] m_data;
}

Matrix Matrix::conventionalMultiplication(const Matrix& l,const Matrix& m)
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
                    result.m_data[i * result.m_size + j] += l.m_data[i * l.m_size + k] * m.m_data[k * m.m_size + j];
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
            result.m_data[i * result.m_size + j] = m_data[i * m_size + j] + m.m_data[i * m.m_size + j];
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
            result.m_data[i * result.m_size + j] = m_data[i * m_size + j] - m.m_data[i * m_size + j];
        }
    }
    return result;
}

bool Matrix::operator ==(const Matrix& m)
{
    if(m_size != m.m_size)
    {
        return false;
    }
    for(int i = 0; i < m_size * m_size; ++i)
    {
        if(m_data[i] != m.m_data[i])
        {
            return false;
        }
    }
    return true;
}

Matrix Matrix::strassenMultiplication(const Matrix& l,const Matrix& r)
{
    if (l.m_size == r.m_size && (l.m_size & (~l.m_size + 1)) == l.m_size) //Check is m_size is power of 2
    {
        if (l.m_size <= m_leafSize)
        {
            return conventionalMultiplication(l,r);
        }
        else
        {
            int newSize = l.m_size / 2;
            Matrix a11(l, newSize, 0);
            Matrix a12(l, newSize, newSize);
            Matrix a21(l, newSize, newSize * l.m_size);
            Matrix a22(l, newSize, newSize * l.m_size + newSize);
            Matrix b11(r, newSize, 0);
            Matrix b12(r, newSize, newSize);
            Matrix b21(r, newSize, newSize * r.m_size);
            Matrix b22(r, newSize, newSize * r.m_size + newSize);

            Matrix m1 = strassenMultiplication(a11 + a22, b11 + b22);   // (a11 + a22) x (b11 + b22)
            Matrix m2 = strassenMultiplication(a21+ a22, b11);          // (a21 + a22) x b11
            Matrix m3 = strassenMultiplication(a11, b12 - b22);         // a11 x (b12 - b22)
            Matrix m4 = strassenMultiplication(a22, b21 - b11);         //a22 x (b21 - b11)
            Matrix m5 = strassenMultiplication(a11 + a12, b22);         //(a11 + a12) x b22
            Matrix m6 = strassenMultiplication(a21 - a11, b11 + b12);   //(a21 - a11) x (b11 + b12)
            Matrix m7 = strassenMultiplication(a12 - a22, b21 + b22);   //(a12 - a22) x (b21 + b22)

            Matrix c11 = m1 + m4 - m5 + m7; // m1 + m4 - m5 + m7
            Matrix c12 = m3 + m5;           // m3 + m5
            Matrix c21 = m2 + m4;           // m2 + m4
            Matrix c22 = m1 - m2 + m3 + m6; // m1 - m2 + m3 + m6
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
            std::cout << m_data[i * m_size + j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Matrix::setLeafSize(int leafSize)
{
    m_leafSize = leafSize;
}
