#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include <vector>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) //Constructor
{
  /** @todo [Part 2] */
  //make new FFI with image png?
  image_ = png; //Shouldnt have to new anything I imagine. 
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  //Should just be able to add the given traversal and colorpicker into the vectors i made to store all of them for animate

  daPick_.push_back(&colorPicker); //Can i just add the references straight to the vectors or do i need to make them pointers?
  daTrav_.push_back(&traversal);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  //So. What do we need to do here
  //The hard part
  //const correct bs
  PNG temp = image_;
  // unsigned int a = 0;
  //We need to go through the traversal vector, and go through each traversal inside of that using an iterator for beginning and end
  for (unsigned int a = 0; a < daTrav_.size(); a++)
  //for (ImageTraversal* a : daTrav_) @check
  {
      ImageTraversal::Iterator end = daTrav_[a]->end(); //So we go through and make an iterator for the end of the current traversal
      // ImageTraversal::Iterator beginning = daTrav_[a]->begin(); And the beginning of the current traversal
      unsigned int overall = 0;
      unsigned int check = 1;
      //ImageTravesal* traverse = 
      for(auto beginning = daTrav_[a]->begin(); beginning != end; ++beginning) //Starting at begin, and while the beginning isnt the end add pixels to the animation
      {
        //Now we need to render the frames during the correct time
        if(overall == 0) //If we are on the first frame add the frame @check
        {
          animation.addFrame(temp);
        }
        if(check % (frameInterval + 1) == 0) //If we are on the frame interval add the frame
        {
          animation.addFrame(temp);
        }
        Point pt = *beginning;
        HSLAPixel hslap = daPick_[a]->getColor(pt.x, pt.y);
        HSLAPixel & pixel = temp.getPixel(pt.x, pt.y);

        pixel = hslap;

        overall ++;
        check ++;
      }
  }
  animation.addFrame(temp); //Should add the last frame. 
  return animation;
}
