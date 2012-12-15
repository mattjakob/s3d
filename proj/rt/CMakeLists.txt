
add_executable(rt main.c)

target_link_libraries(rt ${S3D_LIBRARIES} )

install(TARGETS rt DESTINATION ${BIN_DIR})

