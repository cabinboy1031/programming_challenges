cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(10_todo)
add_executable(todo 
  main.cpp
  item.cpp)
