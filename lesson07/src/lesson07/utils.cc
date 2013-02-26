
#include <IL/il.h>
#include <IL/ilu.h>

#include "lesson07/dbg.h"
#include "lesson07/utils.h"
#include "lesson07/texture.h"


Texture gArrowTexture;
FRect gArrowClips[4];


bool initGL() {
  glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glEnable(GL_TEXTURE_2D);

  checkGL("init failed");

  ilInit();
  ilClearColour(255, 255, 255, 0);

  checkIL("init failed");

  return true;

error:
  return false;
}


void update() {
  // empty
}


void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  gArrowTexture.render(0.f, 0.f, &gArrowClips[0]);
  gArrowTexture.render(SCREEN_WIDTH - gArrowClips[2].w, 0.f, &gArrowClips[1]);
  gArrowTexture.render(0.f, SCREEN_HEIGHT - gArrowClips[2].h, &gArrowClips[2]);
  gArrowTexture.render(SCREEN_WIDTH - gArrowClips[2].w,
      SCREEN_HEIGHT - gArrowClips[2].h, &gArrowClips[3]);

  glutSwapBuffers();
}


bool loadMedia() {
  gArrowClips[0].x = 0.f;
  gArrowClips[0].y = 0.f;

  gArrowClips[1].x = 128.f;
  gArrowClips[1].y = 0.f;

  gArrowClips[2].x = 0.f;
  gArrowClips[2].y = 128.f;

  gArrowClips[3].x = 128.f;
  gArrowClips[3].y = 128.f;

  for (int i = 0; i < 4; i++) {
    gArrowClips[i].w = 128.f;
    gArrowClips[i].h = 128.f;
  }

  return gArrowTexture.loadFromFile("assets/arrows.png");
}
