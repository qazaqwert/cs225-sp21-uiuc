/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"
#include <vector>

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator(); //Default constructor
    //Adding another iterator constructor for the begin
    Iterator(ImageTraversal*, PNG, Point, double); //Takes in an ImageTraversal*, either a BFS or a DFS, an image, a start point, and a tolerance

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);

    /** @todo [Part 1] */
    /** add member functions if neccesary*/

    //Going to need a function to check validity
    bool isValid(Point);

  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
    PNG image_; //Image for the extra constructor
    ImageTraversal * daTrav_; //daTraversal* for the extra constructor
    Point start_; //DaStart point for the extra constructor
    double tolerance_; //DaTolerance for the extra constructor

    //Maybe need an extra point for the valid func and other shit?
    Point position_;

    //Vector of a vector of bools to keep track of whether or not a pixel has been visited
    //Essentially is a 2d vector of bools
    std::vector<std::vector<bool>> beenVisited;

  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  
};
