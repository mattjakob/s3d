# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /opt/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mattjakob/Downloads/s3d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mattjakob/Downloads/s3d/build

# Include any dependencies generated for this target.
include proj/tk/CMakeFiles/tk.dir/depend.make

# Include the progress variables for this target.
include proj/tk/CMakeFiles/tk.dir/progress.make

# Include the compile flags for this target's objects.
include proj/tk/CMakeFiles/tk.dir/flags.make

proj/tk/CMakeFiles/tk.dir/main.c.o: proj/tk/CMakeFiles/tk.dir/flags.make
proj/tk/CMakeFiles/tk.dir/main.c.o: ../proj/tk/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/mattjakob/Downloads/s3d/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object proj/tk/CMakeFiles/tk.dir/main.c.o"
	cd /Users/mattjakob/Downloads/s3d/build/proj/tk && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tk.dir/main.c.o   -c /Users/mattjakob/Downloads/s3d/proj/tk/main.c

proj/tk/CMakeFiles/tk.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tk.dir/main.c.i"
	cd /Users/mattjakob/Downloads/s3d/build/proj/tk && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /Users/mattjakob/Downloads/s3d/proj/tk/main.c > CMakeFiles/tk.dir/main.c.i

proj/tk/CMakeFiles/tk.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tk.dir/main.c.s"
	cd /Users/mattjakob/Downloads/s3d/build/proj/tk && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /Users/mattjakob/Downloads/s3d/proj/tk/main.c -o CMakeFiles/tk.dir/main.c.s

proj/tk/CMakeFiles/tk.dir/main.c.o.requires:
.PHONY : proj/tk/CMakeFiles/tk.dir/main.c.o.requires

proj/tk/CMakeFiles/tk.dir/main.c.o.provides: proj/tk/CMakeFiles/tk.dir/main.c.o.requires
	$(MAKE) -f proj/tk/CMakeFiles/tk.dir/build.make proj/tk/CMakeFiles/tk.dir/main.c.o.provides.build
.PHONY : proj/tk/CMakeFiles/tk.dir/main.c.o.provides

proj/tk/CMakeFiles/tk.dir/main.c.o.provides.build: proj/tk/CMakeFiles/tk.dir/main.c.o

proj/tk/CMakeFiles/tk.dir/tk.c.o: proj/tk/CMakeFiles/tk.dir/flags.make
proj/tk/CMakeFiles/tk.dir/tk.c.o: ../proj/tk/tk.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/mattjakob/Downloads/s3d/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object proj/tk/CMakeFiles/tk.dir/tk.c.o"
	cd /Users/mattjakob/Downloads/s3d/build/proj/tk && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tk.dir/tk.c.o   -c /Users/mattjakob/Downloads/s3d/proj/tk/tk.c

proj/tk/CMakeFiles/tk.dir/tk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tk.dir/tk.c.i"
	cd /Users/mattjakob/Downloads/s3d/build/proj/tk && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /Users/mattjakob/Downloads/s3d/proj/tk/tk.c > CMakeFiles/tk.dir/tk.c.i

proj/tk/CMakeFiles/tk.dir/tk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tk.dir/tk.c.s"
	cd /Users/mattjakob/Downloads/s3d/build/proj/tk && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /Users/mattjakob/Downloads/s3d/proj/tk/tk.c -o CMakeFiles/tk.dir/tk.c.s

proj/tk/CMakeFiles/tk.dir/tk.c.o.requires:
.PHONY : proj/tk/CMakeFiles/tk.dir/tk.c.o.requires

proj/tk/CMakeFiles/tk.dir/tk.c.o.provides: proj/tk/CMakeFiles/tk.dir/tk.c.o.requires
	$(MAKE) -f proj/tk/CMakeFiles/tk.dir/build.make proj/tk/CMakeFiles/tk.dir/tk.c.o.provides.build
.PHONY : proj/tk/CMakeFiles/tk.dir/tk.c.o.provides

proj/tk/CMakeFiles/tk.dir/tk.c.o.provides.build: proj/tk/CMakeFiles/tk.dir/tk.c.o

# Object files for target tk
tk_OBJECTS = \
"CMakeFiles/tk.dir/main.c.o" \
"CMakeFiles/tk.dir/tk.c.o"

# External object files for target tk
tk_EXTERNAL_OBJECTS =

../bin/tk: proj/tk/CMakeFiles/tk.dir/main.c.o
../bin/tk: proj/tk/CMakeFiles/tk.dir/tk.c.o
../bin/tk: proj/tk/CMakeFiles/tk.dir/build.make
../bin/tk: base/laux/liblaux.a
../bin/tk: base/gp/libgp.a
../bin/tk: base/gutil/libgutil.a
../bin/tk: base/geom/libgeom.a
../bin/tk: base/color/libcolor.a
../bin/tk: base/image/libimg.a
../bin/tk: base/lang/liblang.a
../bin/tk: base/poly/libpoly.a
../bin/tk: base/prim/libprim.a
../bin/tk: base/csg/libcsg.a
../bin/tk: base/gener/libgener.a
../bin/tk: base/view/libview.a
../bin/tk: base/clip/libclip.a
../bin/tk: base/raster/libraster.a
../bin/tk: base/shade/libshade.a
../bin/tk: base/scene/libscene.a
../bin/tk: base/hier/libhier.a
../bin/tk: base/visib/libvisib.a
../bin/tk: base/ray/libray.a
../bin/tk: base/rad/librad.a
../bin/tk: base/map/libmap.a
../bin/tk: base/plot/libplot.a
../bin/tk: base/anim/libanim.a
../bin/tk: proj/tk/CMakeFiles/tk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../../../bin/tk"
	cd /Users/mattjakob/Downloads/s3d/build/proj/tk && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
proj/tk/CMakeFiles/tk.dir/build: ../bin/tk
.PHONY : proj/tk/CMakeFiles/tk.dir/build

proj/tk/CMakeFiles/tk.dir/requires: proj/tk/CMakeFiles/tk.dir/main.c.o.requires
proj/tk/CMakeFiles/tk.dir/requires: proj/tk/CMakeFiles/tk.dir/tk.c.o.requires
.PHONY : proj/tk/CMakeFiles/tk.dir/requires

proj/tk/CMakeFiles/tk.dir/clean:
	cd /Users/mattjakob/Downloads/s3d/build/proj/tk && $(CMAKE_COMMAND) -P CMakeFiles/tk.dir/cmake_clean.cmake
.PHONY : proj/tk/CMakeFiles/tk.dir/clean

proj/tk/CMakeFiles/tk.dir/depend:
	cd /Users/mattjakob/Downloads/s3d/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mattjakob/Downloads/s3d /Users/mattjakob/Downloads/s3d/proj/tk /Users/mattjakob/Downloads/s3d/build /Users/mattjakob/Downloads/s3d/build/proj/tk /Users/mattjakob/Downloads/s3d/build/proj/tk/CMakeFiles/tk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : proj/tk/CMakeFiles/tk.dir/depend
