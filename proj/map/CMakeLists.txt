
add_executable(xmap main.c)

target_link_libraries(xmap ${S3D_LIBRARIES} )

install(TARGETS xmap DESTINATION ${BIN_DIR})

