#include <iostream>
#include <string>
#include <cassert>
#include <time.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "logging.h"
#include "shader.h"
#include "model.h"
#include "loadModel.h"

void _update_fps_counter(GLFWwindow *window);

int main(){
  assert(restart_gl_log());
  gl_log("starting GLFW\n%s\n", glfwGetVersionString());
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    gl_log_err("ERROR: could not start GLFW3\n");
    return 1;
  }

  // OpenGL window options
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4); //anti-aliasing

  GLFWmonitor* mon = glfwGetPrimaryMonitor();
  const GLFWvidmode* vmode = glfwGetVideoMode(mon);
  GLFWwindow* window = glfwCreateWindow(vmode->width, vmode->height, "Fun test", mon, NULL);
  if (!window) {
    gl_log_err("ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
  log_gl_params();

  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  // Read our .obj file
  std::vector< glm::vec3 > vertices;
  std::vector< glm::vec2 > uvs;
  std::vector< glm::vec3 > normals; // Won't be used at the moment.
  bool res = loadOBJ("cube.obj", vertices, uvs, normals);

  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  glm::mat4 projection = glm::perspective(
                                          glm::radians(90.0f),
                                          (float) vmode->width / (float)vmode->height,
                                          0.1f,
                                          100.0f);

  // Camera matrix
  glm::mat4 camera = glm::lookAt(
                                 glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
                                 glm::vec3(0,0,0), // and looks at the origin
                                 glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                 );
  // Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 model = glm::mat4(1.0f);

  // Our ModelViewProjection
  glm::mat4 mvp = projection * camera * model; // Remember, matrix multiplication is the other way around

  BufferData<glm::vec3> vbo;
  vbo.set_data(vertices);
  vbo.create_buffer_object();

  Shader default_shader = Shader();
  default_shader.load("default.vert", GL_VERTEX_SHADER);
  default_shader.load("test.frag", GL_FRAGMENT_SHADER);
  default_shader.generate_program();
  // Get a handle for our "MVP" uniform
  // Only during initialisation
  default_shader.link_uniform("MVP",GLSL_UNIFORM_MATRIX_VAR_4_FLOAT);

  Model<glm::vec3> vao;
  vao[VERTEX_POSITION] = vbo;
  vao.create_vertex_object();
  vao.set_shader(default_shader);

  float time = 0.0f;
  while(!glfwWindowShouldClose(window)){
    _update_fps_counter(window);
    time += 0.005f;
    model = glm::rotate(static_cast<float>(sin(time)) / 10,glm::vec3(0,1,0)) * model;
    model = glm::rotate(0.05f,glm::vec3(1,0,0)) * model;
    mvp = projection * camera * model;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
    glUniformMatrix4fv(default_shader.get_uniform_id("MVP"),
                       1,
                       GL_FALSE,
                       &mvp[0][0]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vao.draw(GL_TRIANGLES);

    glfwPollEvents();
    glfwSwapBuffers(window);

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}

void _update_fps_counter(GLFWwindow *window){
  static double previous_seconds = glfwGetTime();
  static int frame_count;
  double current_seconds = glfwGetTime();
  double elapsed_seconds = current_seconds - previous_seconds;
  if (elapsed_seconds > 0.25) {
    previous_seconds = current_seconds;
    double fps = (double)frame_count / elapsed_seconds;
    char tmp[128];
    sprintf(tmp, "opengl @ fps: %.2f", fps);
    glfwSetWindowTitle(window, tmp);
    frame_count = 0;
  }
  frame_count++;
}
