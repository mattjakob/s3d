
add_executable(zsort main.c)

target_link_libraries(zsort ${S3D_LIBRARIES} )

install(TARGETS zsort DESTINATION ${BIN_DIR})
