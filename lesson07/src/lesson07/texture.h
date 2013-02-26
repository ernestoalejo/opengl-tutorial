
#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <string>

#include "lesson07/common.h"
#include "lesson07/opengl.h"
#include "lesson07/rect.h"


class Texture {
public:
  Texture();
  ~Texture();

  bool loadFromPixels(GLuint* pixels, GLuint width, GLuint height);
  bool loadFromFile(const std::string path);
  void render(GLfloat x, GLfloat y, FRect* clip = NULL);

  GLuint id()     { return id_;     }
  GLuint width()  { return width_;  }
  GLuint height() { return height_; }

private:
  GLuint id_, width_, height_;

  void freeTexture();

  DISALLOW_COPY_AND_ASSIGN(Texture);
};


#endif  // TEXTURE_H_
