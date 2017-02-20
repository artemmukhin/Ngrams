#!/bin/bash
cmake CMakeLists.txt &> compile_log
make &>> compile_log