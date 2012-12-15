
add_executable(zflat main.c)

target_link_libraries(zflat ${S3D_LIBRARIES} )

install(TARGETS zflat DESTINATION ${BIN_DIR} )
