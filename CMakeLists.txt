cmake_minimum_required(VERSION 3.12)
project(jtxt)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. DIR_SRCS)

add_executable(jtxt ${DIR_SRCS})