cmake_minimum_required(VERSION 3.5)
project(Ngrams)

set(CMAKE_CXX_STANDARD 11)

find_package (Threads)

set(SOURCE_FILES main.cpp NgramTree.cpp NgramTree.h thpool.h thpool.c)
add_executable(Ngrams ${SOURCE_FILES})

target_link_libraries (Ngrams ${CMAKE_THREAD_LIBS_INIT})
