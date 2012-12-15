
#add_library( img STATIC image.c  libpm.c  libppm.c  image.h  mallocvar.h  pm_config.h  ppm.h )

add_library( img STATIC image.c  image.h  )

install(FILES image.h   DESTINATION ${INCL_DIR})

install(TARGETS img  DESTINATION ${LIB_DIR})
