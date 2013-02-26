
#include <IL/il.h>
#include <IL/ilu.h>

#include "lesson07/dbg.h"
#include "lesson07/texture.h"


Texture::Texture()
: id_(0), width_(0), height_(0) {
  // empty
}

Texture::~Texture() {
  freeTexture();
}

bool Texture::loadFromPixels(GLuint* pixels, GLuint width, GLuint height) {
  freeTexture();

  width_ = width;
  height_ = height;

  glGenTextures(1, &id_);

  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA,
      GL_UNSIGNED_BYTE, pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  checkGL("load texture failed");

  return true;

error:
  return false;
}

bool Texture::loadFromFile(const std::string path) {
  bool r;

  ILuint id = 0;
  ilGenImages(1, &id);
  ilBindImage(id);

  ILboolean success = ilLoadImage(path.c_str());
  if (success != IL_TRUE) {
    log_err("cannot load image: %s", path.c_str());
    return false;
  }

  success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  if (success != IL_TRUE)
    return false;

  r = loadFromPixels(reinterpret_cast<GLuint*>(ilGetData()),
      ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));
  if (!r)
    return false;

  ilDeleteImages(1, &id);
  return true;

error:
  return false;
}

void Texture::freeTexture() {
  if (id_ != 0) {
    glDeleteTextures(1, &id_);
    id_ = 0;
  }
  width_ = height_ = 0;
}

void Texture::render(GLfloat x, GLfloat y, FRect* clip) {
  if (id_ == 0)
    return;

  glLoadIdentity();

  GLfloat top = 0.f, bottom = 1.f, left = 0.f, right = 1.f;
  GLfloat w = width_, h = height_;

  if (clip != NULL) {
    left = clip->x / w;
    right = (clip->x + clip->w) / w;
    top = clip->y / h;
    bottom = (clip->y + clip->h) / h;

    w = clip->w;
    h = clip->h;
  }

  glTranslatef(x, y, 0.f);
  glBindTexture(GL_TEXTURE_2D, id_);
  glBegin(GL_QUADS);
    glTexCoord2f(left, top);
    glVertex2f(0.f, 0.f);

    glTexCoord2f(right, top);
    glVertex2f(w, 0.f);

    glTexCoord2f(right, bottom);
    glVertex2f(w, h);

    glTexCoord2f(left, bottom);
    glVertex2f(0.f, h);
  glEnd();
}
