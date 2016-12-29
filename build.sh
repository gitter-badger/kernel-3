#!/bin/sh

echo "building toolchain"
toolchain/build.sh

echo "building kernel"
mkdir -p build
cd build
cmake ../
make
