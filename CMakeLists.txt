cmake_minimum_required(VERSION 3.23)
project(NHF2)

set(CMAKE_CXX_STANDARD 20)

add_executable(NHF2 main.cpp mapApi.hpp solver.hpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")