
add_library( poly STATIC hpoly.c  poly.c  hpoly.h  poly.h )

install(FILES hpoly.h  poly.h  DESTINATION ${INCL_DIR})

install(TARGETS poly   DESTINATION ${LIB_DIR})
