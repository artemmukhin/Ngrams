#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Release CMakeLists.txt &> compile_log
make &>> compile_log