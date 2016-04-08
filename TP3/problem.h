#pragma once
#include "student.h"
#include <fstream>
struct Problem
{
    Problem(const std::string& filePath);
    Problem(const Problem& problem);
    std::vector<Student> students;
};
