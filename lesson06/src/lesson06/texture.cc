
#include <IL/il.h>

#include "lesson06/dbg.h"
#include "lesson06/texture.h"


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
  ILuint id = 0;
  ilGenImages(1, &id);
  ilBindImage(id);

  ILboolean success = ilLoadImage(path.c_str());
  if (success != IL_TRUE)
    return false;

  success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  if (success != IL_TRUE)
    return false;

  bool r = loadFromPixels(reinterpret_cast<GLuint*>(ilGetData()),
      ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));
  if (!r)
    return false;

  ilDeleteImages(1, &id);
  return true;
}

void Texture::freeTexture() {
  if (id_ != 0) {
    glDeleteTextures(1, &id_);
    id_ = 0;
  }
  width_ = height_ = 0;
}

void Texture::render(GLfloat x, GLfloat y) {
  if (id_ == 0)
    return;

  glLoadIdentity();
  glTranslatef(x, y, 0.f);

  glBindTexture(GL_TEXTURE_2D, id_);
  glBegin(GL_QUADS);
    glTexCoord2f(0.f, 0.f);
    glVertex2f(0.f, 0.f);

    glTexCoord2f(1.f, 0.f);
    glVertex2f(width_, 0.f);

    glTexCoord2f(1.f, 1.f);
    glVertex2f(width_, height_);

    glTexCoord2f(0.f, 1.f);
    glVertex2f(0.f, height_);
  glEnd();
}
