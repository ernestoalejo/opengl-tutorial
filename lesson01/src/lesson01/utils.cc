
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


void update() {
  // empty
}


void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
  glEnd();

  glutSwapBuffers();
}

