FILE(REMOVE_RECURSE
  "csg.c"
  "csg.h"
  "lex.c"
  "CMakeFiles/csg.dir/csg.c.o"
  "CMakeFiles/csg.dir/lex.c.o"
  "CMakeFiles/csg.dir/lang.c.o"
  "CMakeFiles/csg.dir/ops.c.o"
  "libcsg.pdb"
  "libcsg.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/csg.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
