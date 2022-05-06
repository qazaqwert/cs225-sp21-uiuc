/* Your code here! */
#include "maze.h"


SquareMaze::SquareMaze() 
{
    width_ = 0;
    height_ = 0;
}

SquareMaze::~SquareMaze() //might not need this
{

}

bool SquareMaze::canTravel(int x, int y, int dir) const 
{
    return true;
}

cs225::PNG * SquareMaze::drawMaze() const 
{
    return NULL;
}

cs225::PNG * SquareMaze::drawMazeWithSolution() 
{
    return NULL;
}

void SquareMaze::makeMaze(int width, int height) 
{

}

void SquareMaze::setWall(int x, int y, int dir, bool exists) 
{

}

std::vector<int> SquareMaze::solveMaze() 
{
    return std::vector<int>();
}
