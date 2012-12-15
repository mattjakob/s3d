
add_executable(xray main.c)

target_link_libraries(xray ${S3D_LIBRARIES})

install(TARGETS xray DESTINATION ${BIN_DIR})

