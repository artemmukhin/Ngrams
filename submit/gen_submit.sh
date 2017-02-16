#!/bin/bash
mkdir buf
mkdir buf/src
cp ../*.cpp ./buf/src/
cp ../*.c ./buf/src/
cp ../*.h ./buf/src/
cp ../CMakeLists.txt ./buf/src/CMakeLists.txt
cp README buf/
cp compile.sh buf/
cp run.sh buf/
tar -zcvf submission.tar.gz ./buf/