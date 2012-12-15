
add_library( prim  STATIC prim.c  sphere.c  prim.h  sphere.h )

install(FILES prim.h  sphere.h  DESTINATION ${INCL_DIR})

install(TARGETS prim   DESTINATION ${LIB_DIR})
