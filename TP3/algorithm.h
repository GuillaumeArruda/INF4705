#pragma once
#include "solution.h"
class Algorithm
{
public:
    Algorithm();
    virtual ~Algorithm();
    Solution solve(Problem& problem, bool printResult);
private:
    virtual Solution concreteSolve(Problem& problem) = 0;
};

