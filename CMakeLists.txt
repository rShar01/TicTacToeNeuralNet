cmake_minimum_required(VERSION 3.19)
project(tictactoe)

set(CMAKE_CXX_STANDARD 14)

add_executable(tictactoe main.cpp ttc.cpp ttc.h agent_v1.cpp agent_v1.h agent_v2.cpp agent_v2.h Mat.cpp Mat.h)