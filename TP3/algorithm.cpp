#include "algorithm.h"
#include <ctime>
#include <iostream>

Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{
}

Solution Algorithm::solve(Problem& problem, bool printResult)
{
    clock_t start = std::clock();
    Solution bestSolution = concreteSolve(problem);
    #pragma omp parallel
    {
        Problem parallelProblem(problem);
        double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
        while(true)
        {
            Solution solution = concreteSolve(parallelProblem);
            #pragma omp critical
            {
                if(solution.numberOfObstrucatedStudent() < bestSolution.numberOfObstrucatedStudent())
                {
                   bestSolution = solution;
                   if (printResult)
                   {
                       //solution.print();
                       std::cout << "Number of obstrucated student:" << bestSolution.numberOfObstrucatedStudent() << std::endl;
                   }
                }
            }

            duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
        }
    }
   return bestSolution;
}
