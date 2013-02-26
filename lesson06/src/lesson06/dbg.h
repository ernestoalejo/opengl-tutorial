
#ifndef DBG_H_
#define DBG_H_


#include <errno.h>
#include <stdio.h>
#include <string.h>


#ifdef NDEBUG
  #define debug(M, ...)
#else
  #define debug(M, ...) \
    fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif


#define clean_errno() (errno == 0 ? "None" : strerror(errno))


#define log_err(M, ...) \
    fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", \
    __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) \
    fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", \
    __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) \
    fprintf(stderr, "[INFO] (%s:%d) " M "\n", \
    __FILE__, __LINE__, ##__VA_ARGS__)


#define check(A, M, ...) \
    if (!(A)) { \
      log_err(M, ##__VA_ARGS__); \
      errno = 0; \
      goto error; \
    }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) \
    if (!(A)) { \
      debug(M, ##__VA_ARGS__); \
      errno = 0; \
      goto error; \
    }

#define sentinel(M, ...) { \
    log_err(M, ##__VA_ARGS__); \
    errno = 0; \
    goto error; \
  }


#define checkGL(M, ...) { \
    GLenum err = glGetError(); \
    if (err != GL_NO_ERROR) { \
      log_err(M": %s", ##__VA_ARGS__, gluErrorString(err)); \
      goto error; \
    } \
  }


#define checkIL(M, ...) { \
    ILenum err = ilGetError(); \
    if (err != IL_NO_ERROR) { \
      log_err(M": %s", ##__VA_ARGS__, iluErrorString(err)); \
      goto error; \
    } \
  }


#endif  // DBG_H_
