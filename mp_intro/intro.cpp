#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG in;
  in.readFromFile(inputFile);
  cs225::PNG out(in.width(), in.height());
  for (unsigned x = 0; x < in.width(); x++) {
    for (unsigned y = 0; y < in.height(); y++) {
        cs225::HSLAPixel movePixel = in.getPixel(x, y); //ref or no ref?
      //new x pos = width - current x
      //new y pos = height - current y
      out.getPixel(in.width() - 1 - x, in.height() - 1 - y) = movePixel; //assign movePixel to reference output pixel at correct location
      }
    }
    out.writeToFile(outputFile);
  }


cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        cs225::HSLAPixel & pixel = png.getPixel(x, y);
        
          pixel.l = 0.8;
          pixel.s = 1;
          pixel.a = 1;
          if (rand() % 2 >= 1){
          pixel.h = sin((y*3.14)/180)*359;
          }
          else{
            pixel.h = sin((x*3.14)/180)*359;
          }



      }
    }
  return png;
}
