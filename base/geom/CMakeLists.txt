

add_library( geom  STATIC inode.c  matrix.c  ray.c  vector.c  geom.h  ray.h )

install(FILES geom.h  ray.h  DESTINATION ${INCL_DIR})

install(TARGETS geom  DESTINATION ${LIB_DIR})
