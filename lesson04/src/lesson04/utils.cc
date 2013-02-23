
#include "lesson04/dbg.h"
#include "lesson04/utils.h"

GLfloat gCameraX = 0.f, gCameraY = 0.f;


bool initGL() {
  glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();

  glClearColor(0.f, 0.f, 0.f, 1.f);

  checkGL("init failed");

  return true;

error:
  return false;
}


void update() {
  // empty
}


void paintSquare(float r, float g, float b) {
  glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex2f(-SCREEN_WIDTH/4.f, -SCREEN_HEIGHT/4.f);
    glVertex2f(SCREEN_WIDTH/4.f, -SCREEN_HEIGHT/4.f);
    glVertex2f(SCREEN_WIDTH/4.f, SCREEN_HEIGHT/4.f);
    glVertex2f(-SCREEN_WIDTH/4.f, SCREEN_HEIGHT/4.f);
  glEnd();
}


void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glPushMatrix();

  glTranslatef(SCREEN_WIDTH/2.f, SCREEN_HEIGHT/2.f, 0.f);
  paintSquare(1.f, 0.f, 0.f);

  glTranslatef(SCREEN_WIDTH, 0.f, 0.f);
  paintSquare(0.f, 1.f, 0.f);

  glTranslatef(0.f, SCREEN_HEIGHT, 0.f);
  paintSquare(0.f, 0.f, 1.f);

  glTranslatef(-SCREEN_WIDTH, 0.f, 0.f);
  paintSquare(1.f, 1.f, 0.f);

  glutSwapBuffers();
}


void handleKeys(unsigned char key, int x, int y) {
  switch (key) {
  case 'w': gCameraY -= 16.f; break;
  case 's': gCameraY += 16.f; break;
  case 'a': gCameraX -= 16.f; break;
  case 'd': gCameraX += 16.f; break;
  default: return;
  }

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glLoadIdentity();
  glTranslatef(-gCameraX, -gCameraY, 0.f);
  glPushMatrix();
}
