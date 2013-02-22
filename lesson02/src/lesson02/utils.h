
#ifndef UTILS_H_
#define UTILS_H_


#include "lesson02/opengl.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

const int COLOR_MODE_CYAN = 0;
const int COLOR_MODE_MULTI = 1;


bool initGL();
void update();
void render();
void handleKeys(unsigned char key, int x, int y);


#endif  // UTILS_H_

