#include "logging.h"


#define GL_LOG_FILE "gl.log"

bool restart_gl_log() {
  std::ofstream file(GL_LOG_FILE, std::ios::out | std::ios::trunc);
  if(!file.is_open()){
    std::cerr << "ERROR: could not open GL_LOG_FILE log file " << GL_LOG_FILE << " for writing\n";
    return false;
  }
  time_t now = time(NULL);
  char* date = ctime(&now);
  file << "GL_LOG_FILE log. local time" << date << "\n";
  file.close();
  return true;
}

bool gl_log(const char* message, ...){
  va_list argptr;
  FILE* file = fopen(GL_LOG_FILE, "a");
  if(!file) {
    std::cerr << "ERROR: could not open GL_LOG_FILE log file " << GL_LOG_FILE << " for appending\n";
    return false;
  }
  va_start(argptr, message);
  vfprintf(file,message,argptr);
  va_end(argptr);
  fclose(file);
  return true;
}

bool gl_log_err(const char* message, ...){
  va_list argptr;
  FILE* file = fopen(GL_LOG_FILE, "a");
  if(!file) {
    std::cerr << "ERROR: could not open GL_LOG_FILE log file " << GL_LOG_FILE << " for appending\n";
    return false;
  }
  va_start(argptr, message);
  vfprintf(file, message, argptr);
  va_end(argptr);
  va_start(argptr, message);
  vfprintf(stderr, message, argptr);
  va_end(argptr);
  return true;
}

void glfw_error_callback(int error, const char* description){
  gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

void log_gl_params(){
  GLenum params[] = {
    GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
    GL_MAX_CUBE_MAP_TEXTURE_SIZE,
    GL_MAX_DRAW_BUFFERS,
    GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
    GL_MAX_TEXTURE_IMAGE_UNITS,
    GL_MAX_TEXTURE_SIZE,
    GL_MAX_VARYING_FLOATS,
    GL_MAX_VERTEX_ATTRIBS,
    GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
    GL_MAX_VERTEX_UNIFORM_COMPONENTS,
    GL_MAX_VIEWPORT_DIMS,
    GL_STEREO,
  };
  
  const char* names[] = {
    "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
    "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
    "GL_MAX_DRAW_BUFFERS",
    "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
    "GL_MAX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_TEXTURE_SIZE",
    "GL_MAX_VARYING_FLOATS",
    "GL_MAX_VERTEX_ATTRIBS",
    "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
    "GL_MAX_VIEWPORT_DIMS",
    "GL_STEREO",
  };
  
  gl_log("GL Context Params:\n");
  std::string msg;
  
  for(int i = 0; i < 10; i++) {
    int v = 0;
    glGetIntegerv(params[i], &v);
    gl_log("%s %i\n", names[i], v);
  }
  // others
  int v[2];
  v[0] = v[1] = 0;
  glGetIntegerv(params[10], v);
  gl_log("%s %i %i\n", names[10], v[0], v[1]);
  unsigned char s = 0;
  glGetBooleanv(params[11], &s);
  gl_log("%s %u\n", names[11], (unsigned int)s);
  gl_log("-----------------------------\n");
}
