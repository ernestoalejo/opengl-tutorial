
#ifndef UTILS_H_
#define UTILS_H_


#include "lesson04/opengl.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;



bool initGL();
void update();
void render();
void handleKeys(unsigned char key, int x, int y);


#endif  // UTILS_H_

