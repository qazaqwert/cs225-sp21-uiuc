#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  //Constructor
  //Gonna base all of this off of the given pseudocode algorithm from the AMA
  image_ = png; //Initializing all of the variabes to the provided values of png, start, and tolerance
  start_ = start;
  tolerance_ = tolerance;
  //Stack = LIFO
  //Now starting the stack by pushing in the starting point
  dfstack_.push(start_);

}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /**  [Part 1] */
  return ImageTraversal::Iterator(this, image_, start_, tolerance_); //Call the newer iterator constructor to make an iterator with the start
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /**  [Part 1] */
  return ImageTraversal::Iterator(); //Shouldnt need to change this? Just call default constructor
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  dfstack_.push(point); //Just push the point onto the stack that is keeping track of everything
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  Point removal = dfstack_.top(); //Make a new point equal to the top of the stack, aka the value we want to remove
  dfstack_.pop(); //Now pop it off of the stack 
  return removal; //Return the pt we popped off the stack, seems very straightforward, would be easier if pop returned the value popped but oh well
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  return dfstack_.top(); //again seems pretty easy, just show the top of the stack, which is the current point
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /**  [Part 1] */
  if (dfstack_.size() == 0){ //ngl i wrote this and then looked over at the reference for stack and realized .empty() exists, oh well
    return true; // @check if this shit dont work and i have to use the other method
  }
  return false;
}
