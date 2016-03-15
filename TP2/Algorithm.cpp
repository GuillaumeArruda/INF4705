#include "Algorithm.h"
#include <ctime>
#include <iostream>

Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{
}

Solution Algorithm::solve(const Problem& problem, bool printResult, bool printTime)
{
    clock_t start = std::clock();
    Solution solution = concreteSolve(problem);
    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    if (printResult)
    {
        solution.print();
    }
    if(printTime)
    {
        //std::cout << "Duration: " << duration << "s" << std::endl;
        std::cout << problem.locations.size() << ", " << problem.totalChickenProduction << ", " << duration << std::endl;
    }

    return solution;
}
