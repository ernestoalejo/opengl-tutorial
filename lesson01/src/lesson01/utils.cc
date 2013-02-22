
#include "lesson01/dbg.h"
#include "lesson01/utils.h"


bool initGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0.f, 0.f, 0.f, 1.f);

  checkGL("init failed");

  return true;

error:
  return false;
}
