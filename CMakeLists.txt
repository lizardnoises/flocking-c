cmake_minimum_required(VERSION 3.0)
project(boids)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
add_subdirectory(raylib)

add_executable(${PROJECT_NAME} main.c boid.c boid_config.c)
target_link_libraries(${PROJECT_NAME} raylib)
configure_file(config.txt config.txt COPYONLY)
