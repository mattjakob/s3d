
add_library( view STATIC def.c  lang.c  set.c  view.h )

install(FILES view.h  DESTINATION ${INCL_DIR})

install(TARGETS view  DESTINATION ${LIB_DIR})
