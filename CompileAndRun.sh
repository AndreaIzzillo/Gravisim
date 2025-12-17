#!/bin/sh

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
chmod +x ./build/bin/main
./build/bin/main