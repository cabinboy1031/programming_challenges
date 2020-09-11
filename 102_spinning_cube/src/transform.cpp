#include "transform.h"

void Transform::translate(glm::vec3 in){
  glm::mat4 transform = glm::translate(glm::mat4(), in);
  translation = transform * translation;
}

void Transform::rotate(glm::vec3) { /* TODO */ }

void Transform::scale(glm::vec3 in) {
  size = glm::scale(in);
}
void Transform::scale(float x, float y, float z){
  size = glm::scale(glm::vec3(x, y, z));
}
void Transform::scale(float in){
  size = glm::scale(glm::vec3(in, in, in));
}

glm::mat4 Transform::get_transform_matrix(){
  return translation * rotation * size;
}
