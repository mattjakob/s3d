
add_library(gener  STATIC  affine.c  rotsurf.c  gener.h)

install(FILES gener.h  DESTINATION ${INCL_DIR})

install(TARGETS gener  DESTINATION ${LIB_DIR})
