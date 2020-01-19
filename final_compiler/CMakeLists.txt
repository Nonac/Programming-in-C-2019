cmake_minimum_required(VERSION 3.15)
project(compiler C)

set(CMAKE_C_STANDARD 90)

add_executable(compiler nal.c)