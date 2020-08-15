#include <iostream>
#include <string>
#include <cassert>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "logging.h"
#include "shader.h"

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

	// Point object
	float points[] = {
  -0.5f,  0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	Shader test_shader = Shader("test.vert", "test.frag");

	while(!glfwWindowShouldClose(window)){
		_update_fps_counter(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(test_shader.id());
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 1, 4);
		
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
