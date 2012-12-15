
add_library( laux STATIC error.c  io.c  list.c  mem.c  defs.h  laux.h  list.h )

install(FILES defs.h  laux.h  list.h  DESTINATION ${INCL_DIR})

install(TARGETS laux  DESTINATION ${LIB_DIR})
