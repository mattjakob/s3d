
add_executable(splot main.c)

target_link_libraries(splot ${S3D_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL_LIBRARIES} )

install(TARGETS splot DESTINATION ${BIN_DIR})
