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
include cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/depend.make

# Include the progress variables for this target.
include cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/progress.make

# Include the compile flags for this target's objects.
include cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/flags.make

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/flags.make
cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o: ../cvm/application/eventdetect/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-app-eventd.dir/Main.cpp.o -c /home/ubuntu/cvm/cvm/application/eventdetect/Main.cpp

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-app-eventd.dir/Main.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/application/eventdetect/Main.cpp > CMakeFiles/cvm-app-eventd.dir/Main.cpp.i

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-app-eventd.dir/Main.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/application/eventdetect/Main.cpp -o CMakeFiles/cvm-app-eventd.dir/Main.cpp.s

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o.requires:

.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o.requires

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o.provides: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o.requires
	$(MAKE) -f cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/build.make cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o.provides.build
.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o.provides

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o.provides.build: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o


cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/flags.make
cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o: ../cvm/application/eventdetect/EventDetect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o -c /home/ubuntu/cvm/cvm/application/eventdetect/EventDetect.cpp

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/application/eventdetect/EventDetect.cpp > CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.i

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/application/eventdetect/EventDetect.cpp -o CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.s

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o.requires:

.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o.requires

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o.provides: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o.requires
	$(MAKE) -f cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/build.make cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o.provides.build
.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o.provides

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o.provides.build: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o


cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/flags.make
cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o: ../cvm/application/eventdetect/EventDetectConfig.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o -c /home/ubuntu/cvm/cvm/application/eventdetect/EventDetectConfig.cpp

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/application/eventdetect/EventDetectConfig.cpp > CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.i

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/application/eventdetect/EventDetectConfig.cpp -o CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.s

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o.requires:

.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o.requires

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o.provides: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o.requires
	$(MAKE) -f cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/build.make cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o.provides.build
.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o.provides

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o.provides.build: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o


cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/flags.make
cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o: ../cvm/application/eventdetect/ComputeTools.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o -c /home/ubuntu/cvm/cvm/application/eventdetect/ComputeTools.cpp

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/application/eventdetect/ComputeTools.cpp > CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.i

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/application/eventdetect/ComputeTools.cpp -o CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.s

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o.requires:

.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o.requires

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o.provides: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o.requires
	$(MAKE) -f cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/build.make cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o.provides.build
.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o.provides

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o.provides.build: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o


# Object files for target cvm-app-eventd
cvm__app__eventd_OBJECTS = \
"CMakeFiles/cvm-app-eventd.dir/Main.cpp.o" \
"CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o" \
"CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o" \
"CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o"

# External object files for target cvm-app-eventd
cvm__app__eventd_EXTERNAL_OBJECTS =

../bin/cvm-app-eventd: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o
../bin/cvm-app-eventd: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o
../bin/cvm-app-eventd: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o
../bin/cvm-app-eventd: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o
../bin/cvm-app-eventd: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/build.make
../bin/cvm-app-eventd: ../lib/libcvm.a
../bin/cvm-app-eventd: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../../../../bin/cvm-app-eventd"
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cvm-app-eventd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/build: ../bin/cvm-app-eventd

.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/build

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/requires: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/Main.cpp.o.requires
cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/requires: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetect.cpp.o.requires
cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/requires: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/EventDetectConfig.cpp.o.requires
cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/requires: cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/ComputeTools.cpp.o.requires

.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/requires

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/clean:
	cd /home/ubuntu/cvm/build/cvm/application/eventdetect && $(CMAKE_COMMAND) -P CMakeFiles/cvm-app-eventd.dir/cmake_clean.cmake
.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/clean

cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/depend:
	cd /home/ubuntu/cvm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/cvm /home/ubuntu/cvm/cvm/application/eventdetect /home/ubuntu/cvm/build /home/ubuntu/cvm/build/cvm/application/eventdetect /home/ubuntu/cvm/build/cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cvm/application/eventdetect/CMakeFiles/cvm-app-eventd.dir/depend

