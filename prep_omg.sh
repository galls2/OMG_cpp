#!/bin/bash

rm -rf OMG_cpp

git clone https://github.com/galls2/OMG_cpp
cd OMG_cpp
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

cd ../../

cp run_config.omg OMG_cpp/
echo 'Do: cd OMG; ./OMG '

