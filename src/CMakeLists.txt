set(
    SOURCE_FILES
    main.cpp
    shader.cpp
    program.cpp
)

add_executable(libGameXTest ${SOURCE_FILES})
target_link_libraries(libGameXTest PUBLIC GLEW GL glfw)