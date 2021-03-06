#ifndef MODEL_H
#define MODEL_H
#include <map>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "logging.h"
#include "shader.h"
#include "transform.h"

// The vertex buffer object.
template<typename T>
class BufferData {
public:
  BufferData();
  BufferData(std::vector<T> data);

  void set_data(std::vector<T> data);
  //void set_data(T* data);
  void create_buffer_object(); // Buffer finalization

  std::vector<T> data() const { return _data; };
  int size() const { return _size; }
  GLuint id(){ return buffer_id; }
private:
  std::vector<T> _data;
  int _size;
  GLuint buffer_id;
};

/*
 * Common data layers that will be enabled and disabled as needed
 */
enum VertexDataLayer{
  VERTEX_POSITION = 1,
  VERTEX_UV = 2,
  VERTEX_NORMALS = 4,
  VERTEX_COLORS = 8,
  VERTEX_MISC1 = 16,
  VERTEX_MISC = 32
};

/**
 * The primary model object that will the VAO it is assigned.
 * 
 */
template<typename bufferT>
class Model {
public:
  Model();

  BufferData<bufferT>& operator[](VertexDataLayer layer){ return vertex_buffer_data[layer]; }

  // Model finalization
  void create_vertex_object();
  GLuint id() {return vertex_array_object;}
  void set_shader(Shader in){ program = in; };

  Transform get_world_pos();

  void draw(GLenum draw_mode);
private:
  // One per model object. But the vao doesnt need to be remade every time it is copied over.
  // Making a copy of a VAO means taking the assigned data and simply drawing it somewhere else with a different shader.
  GLuint vertex_array_object;
  Transform world_pos;
  Shader program;

  std::map<VertexDataLayer,BufferData<bufferT>> vertex_buffer_data;
};
#endif //MODEL_H
