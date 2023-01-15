cmake_minimum_required(VERSION 3.25)

project(TBBQuestions)

find_package(TBB REQUIRED)
find_package(OpenImageIO REQUIRED)

add_executable(hello_world
  hello_world_main.cpp)

target_link_libraries(hello_world
  PUBLIC
  TBB::tbb)