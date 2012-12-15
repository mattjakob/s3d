
add_library( clip  STATIC clip.c clip.h cull.c twopass.c)

install(FILES clip.h  DESTINATION ${INCL_DIR})

install(TARGETS clip  DESTINATION ${LIB_DIR})
