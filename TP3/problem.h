#pragma once
#include "student.h"
#include <fstream>
struct Problem
{
    Problem(const std::string& filePath);
    std::vector<Student> students;
};