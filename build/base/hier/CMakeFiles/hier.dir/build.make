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
include base/hier/CMakeFiles/hier.dir/depend.make

# Include the progress variables for this target.
include base/hier/CMakeFiles/hier.dir/progress.make

# Include the compile flags for this target's objects.
include base/hier/CMakeFiles/hier.dir/flags.make

base/hier/CMakeFiles/hier.dir/hier.c.o: base/hier/CMakeFiles/hier.dir/flags.make
base/hier/CMakeFiles/hier.dir/hier.c.o: ../base/hier/hier.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/mattjakob/Downloads/s3d/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object base/hier/CMakeFiles/hier.dir/hier.c.o"
	cd /Users/mattjakob/Downloads/s3d/build/base/hier && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/hier.dir/hier.c.o   -c /Users/mattjakob/Downloads/s3d/base/hier/hier.c

base/hier/CMakeFiles/hier.dir/hier.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hier.dir/hier.c.i"
	cd /Users/mattjakob/Downloads/s3d/build/base/hier && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /Users/mattjakob/Downloads/s3d/base/hier/hier.c > CMakeFiles/hier.dir/hier.c.i

base/hier/CMakeFiles/hier.dir/hier.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hier.dir/hier.c.s"
	cd /Users/mattjakob/Downloads/s3d/build/base/hier && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /Users/mattjakob/Downloads/s3d/base/hier/hier.c -o CMakeFiles/hier.dir/hier.c.s

base/hier/CMakeFiles/hier.dir/hier.c.o.requires:
.PHONY : base/hier/CMakeFiles/hier.dir/hier.c.o.requires

base/hier/CMakeFiles/hier.dir/hier.c.o.provides: base/hier/CMakeFiles/hier.dir/hier.c.o.requires
	$(MAKE) -f base/hier/CMakeFiles/hier.dir/build.make base/hier/CMakeFiles/hier.dir/hier.c.o.provides.build
.PHONY : base/hier/CMakeFiles/hier.dir/hier.c.o.provides

base/hier/CMakeFiles/hier.dir/hier.c.o.provides.build: base/hier/CMakeFiles/hier.dir/hier.c.o

base/hier/CMakeFiles/hier.dir/stack.c.o: base/hier/CMakeFiles/hier.dir/flags.make
base/hier/CMakeFiles/hier.dir/stack.c.o: ../base/hier/stack.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/mattjakob/Downloads/s3d/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object base/hier/CMakeFiles/hier.dir/stack.c.o"
	cd /Users/mattjakob/Downloads/s3d/build/base/hier && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/hier.dir/stack.c.o   -c /Users/mattjakob/Downloads/s3d/base/hier/stack.c

base/hier/CMakeFiles/hier.dir/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hier.dir/stack.c.i"
	cd /Users/mattjakob/Downloads/s3d/build/base/hier && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /Users/mattjakob/Downloads/s3d/base/hier/stack.c > CMakeFiles/hier.dir/stack.c.i

base/hier/CMakeFiles/hier.dir/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hier.dir/stack.c.s"
	cd /Users/mattjakob/Downloads/s3d/build/base/hier && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /Users/mattjakob/Downloads/s3d/base/hier/stack.c -o CMakeFiles/hier.dir/stack.c.s

base/hier/CMakeFiles/hier.dir/stack.c.o.requires:
.PHONY : base/hier/CMakeFiles/hier.dir/stack.c.o.requires

base/hier/CMakeFiles/hier.dir/stack.c.o.provides: base/hier/CMakeFiles/hier.dir/stack.c.o.requires
	$(MAKE) -f base/hier/CMakeFiles/hier.dir/build.make base/hier/CMakeFiles/hier.dir/stack.c.o.provides.build
.PHONY : base/hier/CMakeFiles/hier.dir/stack.c.o.provides

base/hier/CMakeFiles/hier.dir/stack.c.o.provides.build: base/hier/CMakeFiles/hier.dir/stack.c.o

# Object files for target hier
hier_OBJECTS = \
"CMakeFiles/hier.dir/hier.c.o" \
"CMakeFiles/hier.dir/stack.c.o"

# External object files for target hier
hier_EXTERNAL_OBJECTS =

base/hier/libhier.a: base/hier/CMakeFiles/hier.dir/hier.c.o
base/hier/libhier.a: base/hier/CMakeFiles/hier.dir/stack.c.o
base/hier/libhier.a: base/hier/CMakeFiles/hier.dir/build.make
base/hier/libhier.a: base/hier/CMakeFiles/hier.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libhier.a"
	cd /Users/mattjakob/Downloads/s3d/build/base/hier && $(CMAKE_COMMAND) -P CMakeFiles/hier.dir/cmake_clean_target.cmake
	cd /Users/mattjakob/Downloads/s3d/build/base/hier && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hier.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
base/hier/CMakeFiles/hier.dir/build: base/hier/libhier.a
.PHONY : base/hier/CMakeFiles/hier.dir/build

base/hier/CMakeFiles/hier.dir/requires: base/hier/CMakeFiles/hier.dir/hier.c.o.requires
base/hier/CMakeFiles/hier.dir/requires: base/hier/CMakeFiles/hier.dir/stack.c.o.requires
.PHONY : base/hier/CMakeFiles/hier.dir/requires

base/hier/CMakeFiles/hier.dir/clean:
	cd /Users/mattjakob/Downloads/s3d/build/base/hier && $(CMAKE_COMMAND) -P CMakeFiles/hier.dir/cmake_clean.cmake
.PHONY : base/hier/CMakeFiles/hier.dir/clean

base/hier/CMakeFiles/hier.dir/depend:
	cd /Users/mattjakob/Downloads/s3d/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mattjakob/Downloads/s3d /Users/mattjakob/Downloads/s3d/base/hier /Users/mattjakob/Downloads/s3d/build /Users/mattjakob/Downloads/s3d/build/base/hier /Users/mattjakob/Downloads/s3d/build/base/hier/CMakeFiles/hier.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : base/hier/CMakeFiles/hier.dir/depend

