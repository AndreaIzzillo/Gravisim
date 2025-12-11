cmake_minimum_required(VERSION 3.28)


project(Gravisim LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Gather source files
file(GLOB CORE_SRC src/core/*.cpp)
file(GLOB BODIES_SRC src/bodies/*.cpp)

# Add simulation library
add_library(simulation STATIC
    ${CORE_SRC}
    ${BODIES_SRC}
)
target_include_directories(simulation PUBLIC src/core src/bodies)
target_link_libraries(simulation PUBLIC SFML::Graphics)

# Main executable
add_executable(main src/main.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE simulation)
