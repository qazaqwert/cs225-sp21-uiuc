#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  //Constructor
  /**  [Part 1] */
  //Alright in the BFS case we shall be using a queue ee you ee and the same stuff as DFS
  image_ = png; //Initializing all of the variabes to the provided values of png, start, and tolerance
  start_ = start;
  tolerance_ = tolerance;
  //Queue = FIFO
  bfsqueue_.push(start_); //Puts the starting point into the beginning of the queue. 
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /**  [Part 1] */
  return ImageTraversal::Iterator(this, image_, start_, tolerance_); //Should be the same as DFS, iterators are magic
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /**  [Part 1] */
  return ImageTraversal::Iterator(); //Should be the same as DFS, iterators are indeed magic.
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /**  [Part 1] */
  //Seems simple like the last one
  bfsqueue_.push(point); //Need to remember the underscores lol
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /**  [Part 1] */
  //Again, same thing as last time essentially
  Point removal = bfsqueue_.front(); //Make a new point equal to the front of the queue
  bfsqueue_.pop(); //Now pop it off of the queue 
  return removal; //return it
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /**  [Part 1] */
  return bfsqueue_.front(); //very simple v nice
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /**  [Part 1] */
  return bfsqueue_.empty(); //wisened up and used the empty() function this time
}
