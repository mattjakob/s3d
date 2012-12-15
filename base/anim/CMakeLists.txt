
add_library(anim STATIC  anim.c anim.h	arg.c time.c)

install(FILES anim.h DESTINATION ${INCL_DIR})

install(TARGETS anim DESTINATION ${LIB_DIR})
