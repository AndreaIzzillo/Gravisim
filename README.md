# Gravisim
Gravisim is a 2D gravity simulation written in C++ using SFML.  
It allows you to create physical bodies, compute their gravitational interactions, and visualize their motion in real time.
Management of resources and variables between layers is not perfectly done, I'll work on it.

## Simulation Scenarios
- **Solar System**: Simulates the Sun and 8 planets with realistic orbits and masses.
- **Three-Body Problem**: Visualizes the chaotic motion of three massive bodies.
- **Circumbinary Trojans**: Simulates a planet orbiting two stars (binary system) with trojan asteroids.
- **Many-Body System**: Generates multiple bodies with random positions and velocities for stress-testing and emergent behavior.

## Features
- 2D Newtonian gravity simulation
- Multiple preset scenarios (Solar System, Three-Body, Circumbinary Trojans, Many-Body)
- Dynamic body creation
- Simulation speed control (fast-forward)
- Trails for visualizing orbits
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

## File Structure
- `src/` — Source code
	- `main.cpp` — Entry point, scenario selection
	- `sim_solarsystem.hpp`, `sim_threebody.hpp`, `sim_circumbinarytrojans.hpp`, `sim_lotofbody.hpp` — Scenario definitions
	- `core/` — Simulation engine and settings
	- `bodies/` — Body and manager classes
