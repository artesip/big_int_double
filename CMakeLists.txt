cmake_minimum_required(VERSION 3.16)
project(mfti_c__)

set(CMAKE_CXX_STANDARD 20)

add_executable(mfti_c__ main.cpp big_double.h big_int.h big_double.cpp big_int.cpp)