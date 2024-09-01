cmake_minimum_required(VERSION 3.25) 
project(argp_exemple)

set(CMAKE_BUILD_TYPE Debug)  
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/lib) 

add_library(argp SHARED  getoptl_ext.c) 
add_executable(${PROJECT_NAME} main.c) 

target_link_libraries(${PROJECT_NAME}  argp)
