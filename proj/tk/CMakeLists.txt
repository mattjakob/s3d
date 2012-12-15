
add_executable(tk main.c tk.c)

target_link_libraries(tk ${S3D_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL_LIBRARIES} )

install(TARGETS tk DESTINATION ${BIN_DIR})
