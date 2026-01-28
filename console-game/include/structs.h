#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>

struct Pig
{
    int Height;
    int Length;
    bool isAlive = true;
};

struct Wall
{
    int Position;
    int Height;
};

struct Level
{
    std::vector<Pig> pigs;
    std::vector<Wall> walls;
    int stars = 0;
    bool isFinished = false;
};

#endif