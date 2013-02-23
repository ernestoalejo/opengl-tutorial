

#include "lesson05/utils.h"


void mainLoop(int val);


int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitContextVersion(2, 1);

  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("Lesson 05");

  if (!initGL())
    return 1;

  if (!loadMedia())
    return 1;

  glutDisplayFunc(render);
  glutTimerFunc(1000./SCREEN_FPS, mainLoop, 0);
  glutMainLoop();

  return 0;
}


void mainLoop(int val) {
  update();
  render();

  glutTimerFunc(100./SCREEN_FPS, mainLoop, val);
}

