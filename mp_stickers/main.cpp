#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image AmongDrip; AmongDrip.readFromFile("AmongDrip.png");
  Image amongtrash; amongtrash.readFromFile("amongtrash.png");
  Image jermasus; jermasus.readFromFile("jermasus.png");
  Image amongnugg; amongnugg.readFromFile("amongnugg.png");
  Image amogus; amogus.readFromFile("amogus.png");
  Image amongdoor; amongdoor.readFromFile("amongdoor.png");
  Image amongfire; amongfire.readFromFile("amongfire.png");
  Image amonghanger; amonghanger.readFromFile("amonghanger.png");
  Image whenthe; whenthe.readFromFile("whenthe.png");
  Image thempissus; thempissus.readFromFile("thempissus.png");
  Image pleasemakeitstop; pleasemakeitstop.readFromFile("pleasemakeitstop.png");
  AmongDrip.scale(1.25);
  amongnugg.scale(0.5);
  amongtrash.scale(0.69);
  amongdoor.scale(0.52069);
  whenthe.scale(2.5);
  thempissus.scale(3);
  pleasemakeitstop.scale(2.5);
  jermasus.scale(1.5);
  amongfire.scale(3);
  StickerSheet Amongus(AmongDrip, 10);
  Amongus.addSticker(amongtrash, 230, 220);
  Amongus.addSticker(amongnugg, 1240, 1380);
  Amongus.addSticker(amogus, 1750, 150);
  Amongus.addSticker(amongdoor, 1350, 550);
  Amongus.addSticker(amongfire, 150, 550);
  Amongus.addSticker(amonghanger, 200, 1300);
  Amongus.addSticker(jermasus, 475, 1450);
  Amongus.addSticker(pleasemakeitstop, 250, 2021);
  Amongus.addSticker(whenthe, 550, 50);
  Amongus.addSticker(thempissus, 400, 1950);


  Amongus.render().writeToFile("myImage.png");
  return 0;
}
