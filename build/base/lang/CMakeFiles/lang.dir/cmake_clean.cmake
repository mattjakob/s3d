FILE(REMOVE_RECURSE
  "parser.c"
  "parser.h"
  "y.tab.h"
  "y.tab.h"
  "CMakeFiles/lang.dir/parser.c.o"
  "CMakeFiles/lang.dir/lex.c.o"
  "CMakeFiles/lang.dir/node.c.o"
  "CMakeFiles/lang.dir/pv.c.o"
  "CMakeFiles/lang.dir/pvl.c.o"
  "CMakeFiles/lang.dir/symbol.c.o"
  "liblang.pdb"
  "liblang.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/lang.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
