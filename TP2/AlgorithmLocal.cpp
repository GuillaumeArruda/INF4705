#include "AlgorithmLocal.h"
#include "AlgorithmVorace.h"


AlgorithmLocal::AlgorithmLocal()
{
}


AlgorithmLocal::~AlgorithmLocal()
{
}

Solution AlgorithmLocal::concreteSolve(const Problem& problem, Solution& solution)
{
    AlgorithmVorace vorace;
    solution = vorace.solve(problem, false);
    return solution;
}
