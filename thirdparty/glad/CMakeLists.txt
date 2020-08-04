cmake_minimum_required(VERSION 2.8.12)

project(glad)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(glad glad.c)