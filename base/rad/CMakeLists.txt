
add_library( rad  STATIC  radiosity.c radiosity.h)

install(FILES radiosity.h  DESTINATION ${INCL_DIR})

install(TARGETS rad  DESTINATION ${LIB_DIR})
