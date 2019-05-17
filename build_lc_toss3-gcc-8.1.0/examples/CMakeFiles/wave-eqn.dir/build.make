# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/tce/packages/cmake/cmake-3.9.2/bin/cmake

# The command to remove a file.
RM = /usr/tce/packages/cmake/cmake-3.9.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0

# Include any dependencies generated for this target.
include examples/CMakeFiles/wave-eqn.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/wave-eqn.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/wave-eqn.dir/flags.make

examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o: examples/CMakeFiles/wave-eqn.dir/flags.make
examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o: ../examples/wave-eqn.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/examples && /usr/tce/packages/gcc/gcc-8.1.0/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o -c /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/examples/wave-eqn.cpp

examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wave-eqn.dir/wave-eqn.cpp.i"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/examples && /usr/tce/packages/gcc/gcc-8.1.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/examples/wave-eqn.cpp > CMakeFiles/wave-eqn.dir/wave-eqn.cpp.i

examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wave-eqn.dir/wave-eqn.cpp.s"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/examples && /usr/tce/packages/gcc/gcc-8.1.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/examples/wave-eqn.cpp -o CMakeFiles/wave-eqn.dir/wave-eqn.cpp.s

examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o.requires:

.PHONY : examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o.requires

examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o.provides: examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/wave-eqn.dir/build.make examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o.provides.build
.PHONY : examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o.provides

examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o.provides.build: examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o


# Object files for target wave-eqn
wave__eqn_OBJECTS = \
"CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o"

# External object files for target wave-eqn
wave__eqn_EXTERNAL_OBJECTS =

bin/wave-eqn: examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o
bin/wave-eqn: examples/CMakeFiles/wave-eqn.dir/build.make
bin/wave-eqn: lib/libRAJA.a
bin/wave-eqn: examples/CMakeFiles/wave-eqn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/wave-eqn"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wave-eqn.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/wave-eqn.dir/build: bin/wave-eqn

.PHONY : examples/CMakeFiles/wave-eqn.dir/build

examples/CMakeFiles/wave-eqn.dir/requires: examples/CMakeFiles/wave-eqn.dir/wave-eqn.cpp.o.requires

.PHONY : examples/CMakeFiles/wave-eqn.dir/requires

examples/CMakeFiles/wave-eqn.dir/clean:
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/examples && $(CMAKE_COMMAND) -P CMakeFiles/wave-eqn.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/wave-eqn.dir/clean

examples/CMakeFiles/wave-eqn.dir/depend:
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/examples /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0 /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/examples /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/examples/CMakeFiles/wave-eqn.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/wave-eqn.dir/depend
