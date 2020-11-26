#ifndef Maze_h
#define Maze_h

#include <iostream>
#include "Mouse.h"

const int WIDTH = 5, HEIGHT = 5;

const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;

const char WAY = '.', WALL = '|', TARGET = 'Q', ENTRYPOINT = 'E', MOUSE = 'M';

struct Scene {
  char maze[WIDTH][HEIGHT] = {
    WAY, WALL, WAY, WAY, WALL,
    WAY, WALL, WAY, WAY, WAY,
    WALL, WAY, WAY, TARGET, WAY,
    WAY, WAY, WALL, WAY, WAY,
    WAY, WAY, WAY, WAY, WAY
  };
};

void renderMazeScene(Scene &scene) {
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      std::cout << scene.maze[i][j] << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

Scene createRandomlyEntrypoint(Scene &scene, Rat &rat) {
  int mazeAlreadyInitialized = 1;

  while(mazeAlreadyInitialized) {
    std::srand(time(NULL));

    int randomPositionAxisX = std::rand() % WIDTH, randomPositionAxisY = std::rand() % HEIGHT;

    if (
      scene.maze[randomPositionAxisX][randomPositionAxisY] != WALL and
      scene.maze[randomPositionAxisX][randomPositionAxisY] != TARGET
    ) {
      scene.maze[randomPositionAxisX][randomPositionAxisY] = ENTRYPOINT;
      rat.axisX = randomPositionAxisX;
      rat.axisY = randomPositionAxisY;

      mazeAlreadyInitialized = 0;
    }
  }

  return scene;
}

bool findCheese (Scene &scene, int axisX, int axisY, bool &hasCheese, int trail) {
  renderMazeScene(scene);

  if (axisX < 0 or axisX >= WIDTH or axisY < 0 or axisY >= HEIGHT)
    return false;

  else if (scene.maze[axisX][axisY] == TARGET) {
    hasCheese = true;
    std::cout << "The mouse found the cheese.\n" << std::endl;

    scene.maze[axisX][axisY] = 'X';

    return true;
  }

  else if (scene.maze[axisX][axisY] == WALL or scene.maze[axisX][axisY] == 'X')
    return false;

  else {
    scene.maze[axisX][axisY] = 'M';

    if (scene.maze[axisX][axisY + 1] != 'M' and trail != RIGHT and findCheese(scene, axisX, axisY + 1, hasCheese, LEFT)) {
      trail = LEFT;
      scene.maze[axisX][axisY] = 'X';
      renderMazeScene(scene);

      return true;
    }

    else if (scene.maze[axisX + 1][axisY] != 'M' and trail != DOWN and findCheese(scene, axisX + 1, axisY, hasCheese, UP)) {
      trail = UP;
      scene.maze[axisX][axisY] = 'X';
      renderMazeScene(scene);

      return true;
    }

    else if (scene.maze[axisX][axisY - 1] != 'M' and trail != LEFT and findCheese(scene, axisX, axisY - 1, hasCheese, RIGHT)) {
      trail = RIGHT;
      scene.maze[axisX][axisY] = 'X';
      renderMazeScene(scene);

      return true;
    }

    else if (scene.maze[axisX - 1][axisY] != 'M' and trail != UP and findCheese(scene, axisX - 1, axisY, hasCheese, DOWN)) {
      trail = DOWN;
      scene.maze[axisX][axisY] = 'X';
      renderMazeScene(scene);

      return true;
    }

    else {
      std::cout << "The mouse is lost and has not managed to get out of the maze.\n";
      std::abort();

      return false;
    }
    return false;
  }
}


#endif
