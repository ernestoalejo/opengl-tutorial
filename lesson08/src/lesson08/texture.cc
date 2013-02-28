
#include <IL/il.h>
#include <IL/ilu.h>

#include "lesson08/dbg.h"
#include "lesson08/texture.h"


Texture::Texture()
: id_(0), width_(0), height_(0), imageWidth_(0), imageHeight_(0) {
  // empty
}

Texture::~Texture() {
  freeTexture();
}

bool Texture::loadFromPixels(GLuint* pixels, GLuint imageWidth,
    GLuint imageHeight, GLuint width, GLuint height) {
  freeTexture();

  imageWidth_ = imageWidth;
  imageHeight_ = imageHeight;
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
  GLuint imgWidth, imgHeight, width, height;
  ILenum err;
  GLuint* data;

  ILuint id = 0;
  ilGenImages(1, &id);
  ilBindImage(id);

  ILboolean success = ilLoadImage(path.c_str());
  check(success == IL_TRUE, "cannot load image: %s", path.c_str());

  success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  check(success == IL_TRUE, "cannot convert image: %s", path.c_str());

  imgWidth = ilGetInteger(IL_IMAGE_WIDTH);
  imgHeight = ilGetInteger(IL_IMAGE_HEIGHT);
  width = powerOfTwo(imgWidth);
  height = powerOfTwo(imgHeight);

  if (imgWidth != width || imgHeight != height) {
    iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
    success = iluEnlargeCanvas(width, height, 1);
    check(success == IL_TRUE, "cannot enlarge image: %s", path.c_str());
  }

  r = loadFromPixels(reinterpret_cast<GLuint*>(ilGetData()),
      imgWidth, imgHeight, width, height);
  check_ret(r);

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
  width_ = height_ = imageWidth_ = imageHeight_ = 0;
}

void Texture::render(GLfloat x, GLfloat y, FRect* clip) {
  if (id_ == 0)
    return;

  glLoadIdentity();

  GLfloat top = 0.f, left = 0.f;
  GLfloat bottom = (GLfloat) imageHeight_ / (GLfloat) height_;
  GLfloat right = (GLfloat) imageWidth_ / (GLfloat) width_;
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

GLuint Texture::powerOfTwo(GLuint n) {
  if (n == 0)
    return n;

  n--;
  n |= (n >> 1);
  n |= (n >> 2);
  n |= (n >> 4);
  n |= (n >> 8);
  n |= (n >> 16);
  return ++n;
}
