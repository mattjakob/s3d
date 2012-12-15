
add_executable(ortho main.c)

target_link_libraries(ortho ${S3D_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL_LIBRARIES} )

install(TARGETS ortho DESTINATION ${BIN_DIR})

