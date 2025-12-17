#!/bin/sh

cmake --build build --config release
chmod +x ./build/bin/Release/main
./build/bin/Release/main