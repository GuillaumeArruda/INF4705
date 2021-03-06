#include "problem.h"
Problem::Problem(const std::string& filePath)
{
    int numberOfStudent;
    int numberOfFriends;
    std::ifstream file;
    file.open(filePath);
    if (file.is_open())
    {
        file >> numberOfStudent;
        file >> numberOfFriends;
        for (int i = 0; i < numberOfStudent; ++i)
        {
            students.push_back(Student());
            students[i].id = i;
            file >> students[i].height;
        }
        for (int i = 0; i < numberOfFriends; ++i)
        {
            int firstFriendId;
            int secondFriendId;
            file >> firstFriendId;
            file >> secondFriendId;
            students[firstFriendId - 1].friends.push_back(&students[secondFriendId - 1]);
            students[secondFriendId - 1].friends.push_back(&students[firstFriendId - 1]);
        }
    }
}

Problem::Problem(const Problem &problem)
{
    for(auto& student : problem.students)
    {
        Student temp;
        temp.height = student.height;
        temp.id = student.id;
        temp.inSolution = false;
        students.push_back(temp);
    }
    for(auto& student : problem.students)
    {
        for(auto& friendOfStudent : student.friends)
        {
            students[student.id].friends.push_back(&students[friendOfStudent->id]);
        }
    }
}
