
add_library( gutil  STATIC cb.c  md.c  mv.c  mvcb.c  cb.h  mv.h )

install(FILES cb.h  mv.h  DESTINATION ${INCL_DIR})

install(TARGETS gutil   DESTINATION ${LIB_DIR})
