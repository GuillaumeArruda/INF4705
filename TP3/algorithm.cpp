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
    Solution bestSolution(problem);
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
                    std::cout << solution.numberOfObstrucatedStudent() << std::endl;
                   bestSolution = solution;
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
