# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/cvm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/cvm/build

# Include any dependencies generated for this target.
include cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/depend.make

# Include the progress variables for this target.
include cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/progress.make

# Include the compile flags for this target's objects.
include cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/flags.make

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/flags.make
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o: ../cvm/application/activesafety/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-app-safety.dir/Main.cpp.o -c /home/ubuntu/cvm/cvm/application/activesafety/Main.cpp

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-app-safety.dir/Main.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/application/activesafety/Main.cpp > CMakeFiles/cvm-app-safety.dir/Main.cpp.i

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-app-safety.dir/Main.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/application/activesafety/Main.cpp -o CMakeFiles/cvm-app-safety.dir/Main.cpp.s

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o.requires:

.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o.requires

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o.provides: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o.requires
	$(MAKE) -f cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/build.make cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o.provides.build
.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o.provides

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o.provides.build: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o


cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/flags.make
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o: ../cvm/application/activesafety/ActiveSafety.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o -c /home/ubuntu/cvm/cvm/application/activesafety/ActiveSafety.cpp

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/application/activesafety/ActiveSafety.cpp > CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.i

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/application/activesafety/ActiveSafety.cpp -o CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.s

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o.requires:

.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o.requires

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o.provides: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o.requires
	$(MAKE) -f cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/build.make cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o.provides.build
.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o.provides

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o.provides.build: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o


cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/flags.make
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o: ../cvm/application/activesafety/ActiveSafetyConfig.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o -c /home/ubuntu/cvm/cvm/application/activesafety/ActiveSafetyConfig.cpp

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/application/activesafety/ActiveSafetyConfig.cpp > CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.i

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/application/activesafety/ActiveSafetyConfig.cpp -o CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.s

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o.requires:

.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o.requires

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o.provides: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o.requires
	$(MAKE) -f cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/build.make cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o.provides.build
.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o.provides

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o.provides.build: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o


cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/flags.make
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o: ../cvm/application/activesafety/CollisionDetec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o -c /home/ubuntu/cvm/cvm/application/activesafety/CollisionDetec.cpp

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/application/activesafety/CollisionDetec.cpp > CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.i

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/application/activesafety/CollisionDetec.cpp -o CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.s

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o.requires:

.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o.requires

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o.provides: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o.requires
	$(MAKE) -f cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/build.make cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o.provides.build
.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o.provides

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o.provides.build: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o


cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/flags.make
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o: ../cvm/application/activesafety/ComputeTools.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o -c /home/ubuntu/cvm/cvm/application/activesafety/ComputeTools.cpp

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/application/activesafety/ComputeTools.cpp > CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.i

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/application/activesafety/ComputeTools.cpp -o CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.s

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o.requires:

.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o.requires

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o.provides: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o.requires
	$(MAKE) -f cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/build.make cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o.provides.build
.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o.provides

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o.provides.build: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o


# Object files for target cvm-app-safety
cvm__app__safety_OBJECTS = \
"CMakeFiles/cvm-app-safety.dir/Main.cpp.o" \
"CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o" \
"CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o" \
"CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o" \
"CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o"

# External object files for target cvm-app-safety
cvm__app__safety_EXTERNAL_OBJECTS =

../bin/cvm-app-safety: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o
../bin/cvm-app-safety: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o
../bin/cvm-app-safety: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o
../bin/cvm-app-safety: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o
../bin/cvm-app-safety: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o
../bin/cvm-app-safety: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/build.make
../bin/cvm-app-safety: ../lib/libcvm.a
../bin/cvm-app-safety: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../../../../bin/cvm-app-safety"
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cvm-app-safety.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/build: ../bin/cvm-app-safety

.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/build

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/requires: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/Main.cpp.o.requires
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/requires: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafety.cpp.o.requires
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/requires: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ActiveSafetyConfig.cpp.o.requires
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/requires: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/CollisionDetec.cpp.o.requires
cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/requires: cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/ComputeTools.cpp.o.requires

.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/requires

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/clean:
	cd /home/ubuntu/cvm/build/cvm/application/activesafety && $(CMAKE_COMMAND) -P CMakeFiles/cvm-app-safety.dir/cmake_clean.cmake
.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/clean

cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/depend:
	cd /home/ubuntu/cvm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/cvm /home/ubuntu/cvm/cvm/application/activesafety /home/ubuntu/cvm/build /home/ubuntu/cvm/build/cvm/application/activesafety /home/ubuntu/cvm/build/cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cvm/application/activesafety/CMakeFiles/cvm-app-safety.dir/depend

