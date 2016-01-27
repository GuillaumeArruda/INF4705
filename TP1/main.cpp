#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>
#include "Matrix.h"


int* parseFileForData(const std::string& filePath, int& size);

int main(int argc, const char* argv[])
{
    bool printResult = false;
    std::string pathToFirstMatrix;
    std::string pathToSecondMatrix;
    pathToFirstMatrix.clear();
    pathToSecondMatrix.clear();
    for(int i = 0; i < argc; ++i)
    {
        if(argv[i][0] == '-')
        {
            switch(argv[i][1])
            {
            case 'p':
                printResult = true;
                break;
            case 'f':
                if(i + 2 < argc)
                {
                    pathToFirstMatrix = argv[++i];
                    pathToSecondMatrix = argv[++i];
                }
                break;
            default:
                break;
            }
        }
    }
    if(!pathToFirstMatrix.empty() && !pathToSecondMatrix.empty())
    {
        int size = 0;
        int* data = parseFileForData(pathToFirstMatrix, size);
        Matrix l(size, data);
        delete[] data;
        data = parseFileForData(pathToSecondMatrix,size);
        Matrix r(size, data);
        clock_t start = std::clock();
        Matrix result = Matrix::strassenMultiplication(l,r);
        double duration = (std::clock() -start) / (double) CLOCKS_PER_SEC;
        std::cout << duration << "s" << std::endl;
        if(printResult)
        {
            result.print();
        }
    }
    else
    {
        std::cout << "You must specify the file paths to two matrices for the software to work" << std::endl;
    }
}


int* parseFileForData(const std::string& filePath, int& size)
{
    std::ifstream file;
    file.open(filePath);
    file >> size;
    size = 1 << size;
    int* data = new int[size * size];
    int i = 0;
    while(file >> data[i])
    {
        i++;
    }
    file.close();
    return data;
}
