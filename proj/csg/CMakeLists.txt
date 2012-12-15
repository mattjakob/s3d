
add_executable(xcsg main.c)

target_link_libraries(xcsg ${S3D_LIBRARIES} )

install(TARGETS xcsg DESTINATION ${BIN_DIR})

