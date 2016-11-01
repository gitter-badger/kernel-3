#!/bin/sh

mkdir -p toolchain/build
cd toolchain/build
cmake ../
make
