
add_executable(xanim main.c)

target_link_libraries(xanim ${S3D_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL_LIBRARIES} )

install(TARGETS xanim DESTINATION ${BIN_DIR})

