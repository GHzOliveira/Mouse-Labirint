#include <iostream>
#include "./utils/Maze.h"
#include "./utils/Mouse.h"

int main() {
  Scene scene;
  Rat rat;
  
  createRandomlyEntrypoint(scene, rat);
  findCheese(scene, rat.axisX, rat.axisY, rat.hasCheese, rat.trail);
  
  return 0;
}
