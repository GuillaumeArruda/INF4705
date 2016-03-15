#include <iostream>
#include "problem.h"
#include "AlgorithmVorace.h"
#include "AlgorithmDynamic.h"
#include "AlgorithmLocal.h"

int main(int argc, const char* argv[])
{
    bool printResult = false;
    std::string filePath;
    Algorithm* algo = NULL;
    for (int i = 0; i < argc; ++i)
    {  
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            case 'p':
            case 'P':
                printResult = true;
                break;
            case 'f':
            case 'F':
                filePath = std::string(argv[++i]);
                break;
            case 'l':
            case 'L':
                algo = new AlgorithmLocal();
                break;
            case 'd':
            case 'D':
                algo = new AlgorithmDynamic();
                break;
            case 'v':
            case 'V':
                algo = new AlgorithmVorace();
                break;
            default:
                break;
            }
        }
    }
    if (algo != NULL)
    {
        if (filePath != std::string())
        {
            Problem problem(filePath);
            algo->solve(problem, printResult);
        }
        else
        {
            std::cout << "A file path must be specified with the -f argument" << std::endl;
        }
    }
    else
    {
        std::cout << "A resolution algorithm must be specified with the -d, -v- or -l argument" << std::endl;
    }
}