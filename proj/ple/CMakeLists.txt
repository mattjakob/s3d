
add_executable(ple main.c)

target_link_libraries(ple ${S3D_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL_LIBRARIES} )

install(TARGETS ple DESTINATION ${BIN_DIR})
