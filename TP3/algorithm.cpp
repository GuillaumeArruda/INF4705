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
    std::cout << bestSolution.numberOfObstrucatedStudent() << std::endl;
    if (printResult)
    {
        bestSolution.print();
    }
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
                   std::cout << bestSolution.numberOfObstrucatedStudent() << std::endl;
                   if (printResult)
                   {
                       solution.print();
                   }
                }
            }

            duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
        }
    }
   return bestSolution;
}
