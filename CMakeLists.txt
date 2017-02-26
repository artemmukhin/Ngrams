cmake_minimum_required(VERSION 3.5)
project(Ngrams)

set(CMAKE_CXX_STANDARD 11)

find_package (Threads)

set(SOURCE_FILES src/main.cpp src/NgramTree.cpp src/NgramTree.h src/Node.cpp src/Node.h src/SuffixList.cpp src/SuffixList.h src/HashTable.cpp src/HashTable.h src/ProcessingThread.cpp src/ProcessingThread.h src/Solver.cpp src/Solver.h)
add_executable(Ngrams ${SOURCE_FILES})

target_link_libraries (Ngrams ${CMAKE_THREAD_LIBS_INIT})
