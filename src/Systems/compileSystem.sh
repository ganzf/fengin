#!/usr/bin/env bash

cd "$1"
rm -rf build
mkdir build
cd build
cmake ..
make
cd ..
cd ..

