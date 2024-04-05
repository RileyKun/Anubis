cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(Anubis LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)

add_library(Anubis SHARED
  src/entry_point.cpp
  src/factory/factory.cpp
)