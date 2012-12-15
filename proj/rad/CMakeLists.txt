
add_executable(xrad main.c mesh.c)

target_link_libraries(xrad ${S3D_LIBRARIES} )

install(TARGETS xrad DESTINATION ${BIN_DIR})

