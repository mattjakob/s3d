
add_executable(rsurf main.c)

target_link_libraries(rsurf ${S3D_LIBRARIES})

install(TARGETS rsurf  DESTINATION ${BIN_DIR})

