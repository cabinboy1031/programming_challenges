#include "model.h"

template<typename T>
BufferData<T>::BufferData(){
}

template<typename T>
BufferData<T>::BufferData(std::vector<T> data){
  _size = data.size();
  _data = data;
}

template<typename T>
void BufferData<T>::set_data(std::vector<T> data){
  _size = data.size();
  _data = data;
}

template<typename T>
void BufferData<T>::create_buffer_object(){
  GLuint buffer_object;
  glGenBuffers(1, &buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_object);
  glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(T) , _data.data(), GL_STATIC_DRAW);
  buffer_id = buffer_object;
}

template<typename bufferT>
Model<bufferT>::Model(){}

template<typename bufferT>
void Model<bufferT>::create_vertex_object(){
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  for(auto& buffer_object : vertex_buffer_data){
    glBindBuffer(GL_ARRAY_BUFFER, buffer_object.second.id());
  }
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

template<typename bufferT>
Transform Model<bufferT>::get_world_pos(){ return Transform(world_pos);}

template<typename bufferT>
void Model<bufferT>::draw(GLenum draw_mode){
  glUseProgram(program.id());
  glBindVertexArray(vertex_array_object);
  glDrawArrays(draw_mode, 0, vertex_buffer_data[VERTEX_POSITION].size() * sizeof(bufferT));
}
