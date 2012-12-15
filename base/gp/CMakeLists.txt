

add_library( gp STATIC  dv.c  font.c  gp.c  font.h  gp.h)

install(FILES font.h  gp.h  DESTINATION ${INCL_DIR})

install(TARGETS gp  DESTINATION ${LIB_DIR})

