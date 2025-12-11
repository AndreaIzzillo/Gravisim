# Gravisim

Gravisim is a 2D gravity simulation written in C++ using SFML.  
It allows you to create physical bodies, compute their gravitational interactions, and visualize their motion in real time.

## Features
- 2D Newtonian gravity simulation  
- Dynamic body creation  
- Simulation speed control (fast-forward)  
- Clean architecture: `Body`, `BodyManager`, `Simulation`

## Dependencies
- C++20  
- SFML 2.6+

## Build
```bash
mkdir build
cd build
cmake ..
make
```
