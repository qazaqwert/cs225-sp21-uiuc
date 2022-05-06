/* Your code here! */
#include "dsets.h"

#include <iostream>
#include <vector>

void DisjointSets::addelements(int num)
{
    //adds non connected nodes to the array
    for (int a = 0; a < num; a++)
    {
        elements.push_back(-1); //root node of uptree stores negative the size, since all are roots, just store a bunch of negatives
    }

}

int DisjointSets::find(int elem)
{
    //From lecture
    //Basically if the current index is negative we need to gtfo
    if (elements[elem] < 0)
    {
        return elem;
    }
    //Now we need to check for the next level if the current one is not negative
    //Each element only exists in one set which is why this works
    //Each index of the array either holds the value of the index the current index points to, or is negative height
    //UpTrees
    //again im p much taking this right from the lecture
    else
    {
        return find(elements[elem]);
    }

}

void DisjointSets::setunion(int a, int b)
{
    //again lecture is helpful
    int root1 = find(a);
    int root2 = find(b);

    int newSize = elements[root1] + elements[root2];

    if (elements[root1] > elements[root2]) //If root one is smaller
    {
        elements[root1] = newSize;
        elements[root2] = root1;
    }
    else
    {
        elements[root1] = root2;
        elements[root2] = newSize;
    }

}

int DisjointSets::size(int elem)
{
    int daInteger = find(elem);
    return elements[daInteger] * -1;
}