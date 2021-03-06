#include "algorithm.h"
#include <iostream>

Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{
}

Solution Algorithm::solve(Problem& problem, bool printResult)
{
    Solution bestSolution = concreteSolve(problem);
    if (printResult)
    {
        bestSolution.print();
    }
    else
    {
        std::cout << bestSolution.numberOfObstrucatedStudent() << std::endl;
    }
    #pragma omp parallel
    {
        Problem parallelProblem(problem);
        while(true)
        {
            Solution solution = concreteSolve(parallelProblem);
            #pragma omp critical
            {
                
                if(solution.numberOfObstrucatedStudent() < bestSolution.numberOfObstrucatedStudent() || !bestSolution.isValid())
                {
                   bestSolution = solution;
                   std::cout << bestSolution.numberOfObstrucatedStudent() << std::endl;
                   if (printResult)
                   {
                       solution.print();
                   }
                }
            }
        }
    }
   return bestSolution;
}
