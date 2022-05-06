
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

#include <cmath>

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  //From part 2 of tests
  PNG image;
  image.readFromFile("watamelon.png");
  FloodFilledImage filledPic(image);

  MyColorPicker color;

  BFS dfs(image, Point(100, 100), .01);
  filledPic.addFloodFill(dfs, color);

  BFS bfs1(image, Point(500, 600), 0.2);
  filledPic.addFloodFill(bfs1, color);

  BFS bfs2(image, Point(270, 470), 0.2);
  filledPic.addFloodFill(bfs2, color);

  BFS bfs3(image, Point(350, 350), 0.2);
  filledPic.addFloodFill(bfs3, color);

  BFS bfs4(image, Point(470, 270), 0.2);
  filledPic.addFloodFill(bfs4, color);

  BFS bfs5(image, Point(570, 300), 0.2);
  filledPic.addFloodFill(bfs5, color);

  BFS bfs6(image, Point(590, 550), 0.2);
  filledPic.addFloodFill(bfs6, color);

  BFS bfs7(image, Point(666, 465), 0.2);
  filledPic.addFloodFill(bfs7, color);


  Animation anim = filledPic.animate(50000);

  
  PNG lastFrame = anim.getFrame( anim.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  anim.write("myFloodFill.gif");
  


  return 0;
}
