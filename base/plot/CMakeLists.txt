
add_library( plot  STATIC  ortho.c  plot.c  ortho.h  plot.h)

install(FILES  ortho.h  plot.h   DESTINATION ${INCL_DIR})

install(TARGETS plot  DESTINATION ${LIB_DIR})
