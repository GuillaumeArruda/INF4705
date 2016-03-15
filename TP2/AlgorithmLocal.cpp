#include "AlgorithmLocal.h"
#include "AlgorithmVorace.h"


AlgorithmLocal::AlgorithmLocal()
{
}


AlgorithmLocal::~AlgorithmLocal()
{
}

Solution AlgorithmLocal::concreteSolve(const Problem& problem)
{
    AlgorithmVorace vorace;
    Solution solution(problem);
    solution = vorace.solve(problem, false);
    return solution;
}
