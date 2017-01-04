#!/bin/sh

wget https://cmake.org/files/v3.7/cmake-3.7.1-Linux-x86_64.sh
chmod +x cmake-3.7.1-Linux-x86_64.sh
sudo ./cmake-3.7.1-Linux-x86_64.sh --prefix=/usr/local --skip-license
