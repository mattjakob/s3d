

add_definitions( -D VIEW_LIB -D SHADE_LIB )

add_library( scene STATIC obj.c  scene.c  obj.h  scene.h )

install(FILES obj.h  scene.h  DESTINATION ${INCL_DIR})

install(TARGETS scene  DESTINATION ${LIB_DIR})
