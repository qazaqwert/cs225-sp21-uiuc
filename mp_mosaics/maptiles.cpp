/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;

Point<3> convertToXYZ(LUVAPixel pixel)
{
    return Point<3>(pixel.l, pixel.u, pixel.v);
}

MosaicCanvas *mapTiles(SourceImage const &theSource, vector<TileImage> &theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> vectorTiles;   //vectorTiles, da vector with the tiles on it
    map<Point<3>, int> mapTiles;    //make the map n shit

    if (theTiles.empty()) //edge cases? I mean it said we didnt have to worry about them but here we are
    {
        return NULL;
    }
    if (!theSource.getRows())
    {
        return NULL;
    }
    if (!theSource.getColumns())
    {
        return NULL;
    }

    for (unsigned a = 0; a < theTiles.size(); a++) //int dont work maybe cuz data size is very very large OwO
    {
        LUVAPixel avgColor = theTiles[a].getAverageColor(); //makes a LUVAPixel with the averagecolor value from each of the times
        Point<3> avgPoint = convertToXYZ(avgColor);         //converts the LUVA to XYZ
        vectorTiles.push_back(avgPoint);                    //puts the xyz avg color onto the vector
        mapTiles[avgPoint] = a;                             //puts the xyz avg color onto the map
    }

    KDTree<3> KDtree(vectorTiles); //make the tree that stores the avg colors

    MosaicCanvas *output = new MosaicCanvas(theSource.getRows(), theSource.getColumns()); //create the new dynamically allocated MosaicCanvas with rows and columns of source

    for (int n = 0; n < theSource.getRows(); n++)
    {
        for (int m = 0; m < theSource.getColumns(); m++) //go over the tiles areas in the source image and get their colors, then put them into the new output
        {
            Point<3> tileVal = convertToXYZ(theSource.getRegionColor(n, m));
            Point<3> tileNear = KDtree.findNearestNeighbor(tileVal);
            output->setTile(n, m, &theTiles[mapTiles[tileNear]]);
        }
    }

    return output;
}
