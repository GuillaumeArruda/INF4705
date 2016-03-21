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
        friends.resize(numberOfStudent);
        for (int i = 0; i < numberOfFriends; ++i)
        {
            int firstFriendId;
            int secondFriendId;
            file >> firstFriendId;
            file >> secondFriendId;
            friends[firstFriendId - 1].push_back(secondFriendId - 1);
            friends[secondFriendId - 1].push_back(firstFriendId - 1);
        }
    }
}