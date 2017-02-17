#!/bin/bash
cd src
cmake CMakeLists.txt &> compile_log
make &>> compile_log
cd ..