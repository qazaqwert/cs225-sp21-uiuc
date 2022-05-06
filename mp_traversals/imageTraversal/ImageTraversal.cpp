#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include <vector> //idk if i need to do this or not?

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** [Part 1] */
  //brain hurty
  //Okay. So. This is default iterator
  //We need to initialize the Iterator to null
  daTrav_ = NULL;
  //now let's get the width and height of the image into some variables to iterate through to set all of the bools to 0
  int imgW = image_.width();
  int imgH = image_.height(); 
  //Ah, i see why this wasnt working, i forgot to resize the vector before assigning the values, cant assign a value to something
  //that doesnt exist
  beenVisited.resize(imgW);
  for(int width = 0; width < imgW; width ++)
  {
    //also need to resize each subvector before going into them to do the bool falsing
    beenVisited[width].resize(imgH); //beenVisited[width] is a vector so you can resize it as well
    for(int height = 0; height < imgH; height ++)
    {
      beenVisited[width][height] = 0; //Should go through the vector setting all the visit checks to 0
      //@check
    }
  }


}
ImageTraversal::Iterator::Iterator(ImageTraversal* trav, PNG base, Point point, double tol) 
{ //The new iterator for the begin state
  //Should be very similar to the other one, except this time we take in more shit
  daTrav_ = trav; //Initialize iterator to the one from the function input
  //Then just go down and put all the private vars we added equal to the inputs
  image_ = base; 
  start_ = point;
  position_ = point;
  tolerance_ = tol;

  //now get the width and height of the image again
  int imgW = image_.width();
  int imgH = image_.height(); 
  //And go through the visited vector
  //Ah, i see why this wasnt working, i forgot to resize the vector before assigning the values, cant assign a value to something
  //that doesnt exist
  beenVisited.resize(imgW);
  for(int width = 0; width < imgW; width ++)
  {
    //also need to resize each subvector before going into them to do the bool falsing
    beenVisited[width].resize(imgH); //beenVisited[width] is a vector so you can resize it as well
    for(int height = 0; height < imgH; height ++)
    {
      beenVisited[width][height] = 0; //Should go through the vector setting all the visit checks to 0
      //@check for unsigned vs signed int
    }
  }

  //Oh shit we already visited this first one technicall so we need to make that one true
  beenVisited[start_.x][start_.y] = 1; //@check if it doesnt work change to true instead of 1;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //Basically just going to do what the AMA slide said to 
  //So i need to make a 2d vector (vector of vectors) for keeping track of whether or not a point has been visited <- done in constructor
  //1. Gets an empty stack or queue S -> In this case it is the daTrav_ ImageTraversal made in constructor
  //2. Initializes the current as start_ -> done in constructor?
  //3. Marks current as visited
  //4. Push current and its neighbors to S
  //5. Until S is empty or pt isnt visited and within tolerance, point = S.pop()
  //6. If S isnt empty
    //a. Set current = pt
    //b. Go back to 3
  //7. If S is empty we are done

  //1. Done in constructor
  //2. Should be done in constructor? @check
  //3.
  beenVisited[position_.x][position_.y] = 1; //@check if 1 == true like it should, also this just makes the visited be true
  //4. 
  //current should already be on S
  //Now create points for the neighbors and push them onto S
  Point Left = Point(position_.x - 1, position_.y); //Left is one to the left
  Point Right = Point(position_.x + 1, position_.y); //Right is one to the right
  Point Up = Point(position_.x, position_.y - 1); //Up is MINUS ONE NOT PLUS ONE YOU RETARD
  Point Down = Point(position_.x, position_.y + 1); //Down is PLUS ONE NOT MINUS ONE YOU RETARD
  //Now maybe to save a step check if valid before adding to S?
  //Checks to see if each point is valid, if so add it to S. 
  if (isValid(Right))
  {
    daTrav_->add(Right);
  }
  if (isValid(Down))
  {
    daTrav_->add(Down);
  }
  if (isValid(Left))
  {
    daTrav_->add(Left);
  }
  
  if (isValid(Up))
  {
    daTrav_->add(Up);
  }
  
  //5. and 6.
  while((daTrav_->empty() == 0) && (isValid(daTrav_->peek()) == 0)) //While the S isnt empty, and the point isnt Valid (been visited or isnt in tolerance)
  {
    daTrav_->pop();
  }
  //7. Test
  if(daTrav_->empty() == 1) //If the traversal is empty after doing all the pops possible
  {
    daTrav_ = NULL; //The trav is NULL
  }
  else if(true)
  {
    position_ = daTrav_->peek(); //Make the new position equal to whatever is on top of the traversal
  }


  return *this; //This should be correct
}

bool ImageTraversal::Iterator::isValid(Point check) //Takes in a point and returns whether or not it is valid
{
  //First check to see if the point is oob if yes, return false, if no continue
  //Then if it isnt oob check to see if its in tolerance using the calculateDelta function, if yes continue, if no return false
  //Then if it isnt oob and is in tolerance, check to see if it has been visited already, if yes return false, if no return true
  Point holder = check;
  if (holder.x >= image_.width() || holder.y >= image_.height()) //@check - if it doesnt work maybe try changing to just >
  {
    return false; //If the point is oob return false
  }
  //std::cout << "After first valid check";
  if ( (calculateDelta(image_.getPixel(start_.x, start_.y), image_.getPixel(holder.x, holder.y)) < tolerance_) 
                        && (beenVisited[holder.x][holder.y] == false)) //If the delta is < tolerance and the pixel hasnt been visited already
                        //@check - might need <=
  {
    return true;
  }
return false;
}

/**
 * sterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  //Just needs to return current point? Should be maintained by ++ when iterator is iterated. 
  return position_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other)
{
  //copped this from the != from lab trees, hope that is fine
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (daTrav_ == NULL) { thisEmpty = true; }
  if (other.daTrav_ == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = daTrav_->empty(); }
  if (!otherEmpty) { otherEmpty = other.daTrav_->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (daTrav_ != other.daTrav_); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
}

