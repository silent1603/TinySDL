#!/bin/bash

if [ ! -d "./build" ]; then
    mkdir build
fi
cd build 
cmake ..
make
cd ..
bash ./run.sh