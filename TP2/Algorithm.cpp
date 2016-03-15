#include "Algorithm.h"
#include <ctime>
#include <iostream>

Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{
}

Solution Algorithm::solve(const Problem& problem, bool printResult)
{
    Solution solution(problem);
    clock_t start = std::clock();
    concreteSolve(problem, solution);
    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    if (printResult)
    {
        solution.print();
    }
    std::cout << "Duration: " << duration << "s" << std::endl;
    return solution;
}
