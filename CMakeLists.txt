cmake_minimum_required(VERSION 3.17)
project(Collector)

set(CMAKE_CXX_STANDARD 14)

add_executable(Collector main.cpp Node.h Collector.cpp Collector.h)