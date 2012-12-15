
add_library(color  STATIC conv.c index.c rgbhsv.c color.h )

install(FILES color.h  DESTINATION ${INCL_DIR})

install(TARGETS color  DESTINATION ${LIB_DIR})
