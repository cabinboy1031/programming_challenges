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
  glm::vec3 translation;
  glm::vec3 rotation; // Rotation in degrees
  glm::vec3 size;

  void translate(glm::vec3);
  void rotate(glm::vec3);
  void scale(glm::vec3);
};

class BufferData {
public:
  BufferData();
  BufferData(GLfloat &data, int width, int points);
  ~BufferData();
  BufferData(BufferData &);
  BufferData(BufferData &&);

  GLfloat& get_data() const { return *data; };
  int size() const { return width * points; }
private:
  GLfloat *data;
  int width,
      points;
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

class Model {
public:
  Model();
  Model(GLfloat& model_buffer_data);

  Transform get_world_pos();

  void draw(GLenum draw_mode);
private:
  std::map<VertexDataLayer,std::vector<float>> vertex_buffer_data;
  Transform world_pos;
  Shader program;

  std::map<VertexDataLayer,GLuint> vertex_buffer_objects; 
  GLuint vertex_array_object;
};
