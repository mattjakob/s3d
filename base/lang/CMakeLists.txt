
BISON_TARGET(parser_c parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)

BISON_TARGET(parser_h parser.y ${CMAKE_CURRENT_BINARY_DIR}/y.tab.h)

add_library( lang  STATIC ${BISON_parser_c_OUTPUTS}  ${BISON_parser_h_OUTPUTS}   lex.c  node.c  pv.c  pvl.c  symbol.c  lang.h  sdltypes.h  symbol.h )

install(FILES lang.h  sdltypes.h  symbol.h  DESTINATION ${INCL_DIR})

install(TARGETS lang  DESTINATION ${LIB_DIR})
