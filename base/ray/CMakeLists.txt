
add_library( ray STATIC  rshade.c rshade.h)

install(FILES rshade.h  DESTINATION ${INCL_DIR})

install(TARGETS  ray   DESTINATION ${LIB_DIR})
