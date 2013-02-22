
#ifndef UTILS_H_
#define UTILS_H_


#include "lesson03/opengl.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;


enum ViewPortMode {
  VIEWPORT_MODE_FULL,
  VIEWPORT_MODE_HALF_CENTER,
  VIEWPORT_MODE_HALF_TOP,
  VIEWPORT_MODE_QUAD,
  VIEWPORT_MODE_RADAR,
};


bool initGL();
void update();
void render();
void handleKeys(unsigned char key, int x, int y);


#endif  // UTILS_H_

