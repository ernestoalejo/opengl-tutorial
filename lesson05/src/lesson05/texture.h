
#ifndef TEXTURE_H_
#define TEXTURE_H_


#include "opengl.h"
#include "common.h"


class Texture {
public:
  Texture();
  ~Texture();

  bool loadFromPixels(GLuint* pixels, GLuint width, GLuint height);
  void render(GLfloat x, GLfloat y);

  GLuint id()     { return id_;     }
  GLuint width()  { return width_;  }
  GLuint height() { return height_; }

private:
  GLuint id_, width_, height_;

  void freeTexture();

  DISALLOW_COPY_AND_ASSIGN(Texture);
};


#endif  // TEXTURE_H_
