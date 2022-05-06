/* Your code here! */
#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <iostream>
#include <utility>

class SquareMaze
{
    public:
    SquareMaze();
    ~SquareMaze(); //Do i need this?
    bool canTravel(int x, int y, int dir) const;
    cs225::PNG * drawMaze() const;
    cs225::PNG * drawMazeWithSolution();
    void makeMaze(int width, int height);
    void setWall(int x, int y, int dir, bool exists);
    std::vector<int> solveMaze(); //Will probably need some sort of helper function for this but idk.

    

    private:
        //What do we need in here owo
        //probably width and height
        int width_;
        int height_;
        //So the maze is an array of nodes with a down and a right bool?
        std::vector<std::pair<bool, bool> > maze_; //maze
        std::vector<bool> beenVisited_; //vector of bools to keep track of what has been visited

};