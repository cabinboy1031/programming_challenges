#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
