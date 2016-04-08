#pragma once
#include "student.h"
#include "problem.h"
#include <iostream>

struct Solution
{
    Solution(Problem& problem);
    bool isValid();
    void print();
    int numberOfObstrucatedStudent();
    Problem* m_problem;
    std::vector<Student*> students;
};
