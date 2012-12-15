
add_executable(zmap main.c)

target_link_libraries(zmap ${S3D_LIBRARIES} )

install(TARGETS zmap DESTINATION ${BIN_DIR})
