cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(nlohmann_json 3.2.0 REQUIRED)

project(10_todo)
add_executable(todo 
  main.cpp
  item.cpp)

target_link_libraries(todo PRIVATE nlohmann_json::nlohmann_json)
