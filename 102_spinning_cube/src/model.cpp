#include "model.h"
void Transform::translate(glm::vec3){ /* TODO */ }
void Transform::rotate(glm::vec3) { /* TODO */ }
void Transform::scale(glm::vec3) { /* TODO */ }

BufferData::BufferData(){/* TODO */}
BufferData::BufferData(GLfloat &data, int width, int points){/* TODO */ }
BufferData::BufferData(BufferData &in){ /* TODO */ }
BufferData::BufferData(BufferData &&in){ /* TODO */ }

Model::Model(GLfloat& model_buffer_data){ /* TODO */ }

Transform Model::get_world_pos(){ /* TODO */ return Transform();}
void Model::draw(GLenum draw_mode){ /* TODO */}


