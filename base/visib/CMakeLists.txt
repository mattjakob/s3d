
add_library( visib  STATIC  rt.c  rtcsg.c  zbuf.c  zsort.c  rt.h rtcsg.h  zbuf.h  zsort.h )

install(FILES rt.h rtcsg.h  zbuf.h  zsort.h  DESTINATION ${INCL_DIR})

install(TARGETS visib  DESTINATION ${LIB_DIR})
