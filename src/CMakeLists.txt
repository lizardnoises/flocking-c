add_executable(${PROJECT_NAME} main.c boid.c boid_config.c)
target_link_libraries(${PROJECT_NAME} raylib)

add_custom_command(TARGET boids POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/config.txt"
        $<TARGET_FILE_DIR:boids>)