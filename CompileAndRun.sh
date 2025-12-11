#!/bin/sh

cmake --build build
chmod +x ./build/bin/main
./build/bin/main