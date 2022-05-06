#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

#include <cmath>

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  
  unsigned hue = std::cos(x) * y/1000;
  //x * y;
  //

  hue = hue % 360;
  if (hue > 155)
  {
    hue = hue % 155;
  }
  if (hue < 55)
  {
    hue = 155 - hue;
  }

  return HSLAPixel(hue, 1, 0.5);
}
