#ifndef MODEL_H
#define MODEL_H
#include <map>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "logging.h"
#include "shader.h"

struct Transform{
  glm::mat4 translation;
  glm::mat4 rotation; // Rotation in degrees
  glm::mat4 size;

  void translate(glm::vec3);
  void rotate(glm::vec3);
  void scale(glm::vec3);
  void scale(float, float, float);
  void scale(float);
  glm::mat4 get_transform_matrix();
};

// The vertex buffer object.
class BufferData {
public:
  BufferData();
  BufferData(std::vector<GLfloat> data);

  void set_data(std::vector<GLfloat> data);
  void create_buffer_object(); // Buffer finalization

  std::vector<GLfloat> data() const { return _data; };
  int size() const { return _size; }
  GLuint id(){ return buffer_id; }
private:
  std::vector<GLfloat> _data;
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
class Model {
public:
  Model();

  BufferData& operator[](VertexDataLayer layer){ return vertex_buffer_data[layer]; }

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

  std::map<VertexDataLayer,BufferData> vertex_buffer_data;
};
#endif //MODEL_H
