cmake_minimum_required(VERSION 3.16.3)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions(
   -g
   -std=c++11
   -Wall
   -Werror
   -Wextra
   -pedantic
   -Wuninitialized
)

add_library(
   EcuM.lib
   ../src/EcuM.cpp
)

include_directories(
   "${PROJECT_SOURCE_DIR}/../gen/"
)

