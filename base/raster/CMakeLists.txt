
add_library( raster  STATIC scan_obj.c  scan_space.c  subdiv_obj.c  subdiv_space.c  raster.h  scan_obj.h )

install(FILES raster.h  scan_obj.h DESTINATION ${INCL_DIR})

install(TARGETS raster  DESTINATION ${LIB_DIR})
