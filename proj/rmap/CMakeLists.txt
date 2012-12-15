
add_executable(rmap main.c)

target_link_libraries(rmap ${S3D_LIBRARIES} )

install(TARGETS rmap DESTINATION ${BIN_DIR})

