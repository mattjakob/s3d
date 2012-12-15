
add_library( map STATIC  funcs.c  image.c  lang.c  light.c  map.c  material.c  shade.c  map.h )

install(FILES map.h  DESTINATION ${INCL_DIR})

install(TARGETS map  DESTINATION ${LIB_DIR})
