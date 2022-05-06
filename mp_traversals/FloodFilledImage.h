/**
 * @file FloodFilledImage.h
 * Definition for a class to do flood fill on an image
 */
#pragma once

#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"

using namespace cs225;
/**
 * This class is used to do flood fill on an image.
 * One or more FloodFill operations will be added and executed in the order they
 * are added in. Each operation should flood-fill the entire image. Each operation
 * should have its own traversal method and color picker.
 */
class FloodFilledImage {
public:
  FloodFilledImage(const PNG & png);
  void addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker);
  Animation animate(unsigned frameInterval) const;

private:
	/** @todo [Part 2] */
	/** add private members here*/
  //Gonna need a png, and an imagetraversal * vector and colorpicker* vector, for constructor, and add respectively
  PNG image_;

  std::vector<ImageTraversal*> daTrav_; //I never know if i need to use std:: or not
  std::vector<ColorPicker*> daPick_;

};
