

#include "lesson02/utils.h"


void mainLoop(int val);


int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitContextVersion(2, 1);

  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("Lesson 02");

  if (!initGL())
    return 1;

  glutDisplayFunc(render);
  glutKeyboardFunc(handleKeys);
  glutTimerFunc(1000./SCREEN_FPS, mainLoop, 0);
  glutMainLoop();

  return 0;
}


void mainLoop(int val) {
  update();
  render();

  glutTimerFunc(100./SCREEN_FPS, mainLoop, val);
}

