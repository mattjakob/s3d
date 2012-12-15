
add_executable(vw main.c)

target_link_libraries(vw ${S3D_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL_LIBRARIES} )

install(TARGETS vw DESTINATION ${BIN_DIR})
