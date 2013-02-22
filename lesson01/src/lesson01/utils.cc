
#include "lesson01/dbg.h"
#include "lesson01/utils.h"


bool initGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0.f, 0.f, 0.f, 1.f);

  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    printf("init error: %s\n", gluErrorString(error));
    return false;
  }

  return true;
}
