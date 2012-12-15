
add_library( hier STATIC hier.c  stack.c  hier.h  stack.h )

install(FILES hier.h  stack.h  DESTINATION ${INCL_DIR})

install(TARGETS hier  DESTINATION ${LIB_DIR})
