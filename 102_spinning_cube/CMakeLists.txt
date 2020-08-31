cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_BUILD_TYPE Debug)
project(cube)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)

add_executable(cube
	src/main.cpp
	src/shader.cpp
	src/logging.cpp
	src/model.cpp)

add_library(cabinGL
  src/shader.cpp
  src/logging.cpp
  src/model.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/shader/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

include_directories(
	${GLFW_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIRS}
	${GLUT_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	)


target_link_libraries(cube
	glfw
	OpenGL::GL
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLUT_LIBRARIES}
	)

target_link_libraries(cabinGL
	glfw
	OpenGL::GL
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLUT_LIBRARIES}
	)
