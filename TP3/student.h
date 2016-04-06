#pragma once
#include <vector>

struct Student
{
    int id;
    int height;
    bool inSolution = false;
    std::vector<Student*> friends;
};
