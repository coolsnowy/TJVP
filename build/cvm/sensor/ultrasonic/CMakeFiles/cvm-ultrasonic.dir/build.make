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
include cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/depend.make

# Include the progress variables for this target.
include cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/progress.make

# Include the compile flags for this target's objects.
include cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/flags.make

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/flags.make
cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o: ../cvm/sensor/ultrasonic/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o -c /home/ubuntu/cvm/cvm/sensor/ultrasonic/Main.cpp

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-ultrasonic.dir/Main.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/sensor/ultrasonic/Main.cpp > CMakeFiles/cvm-ultrasonic.dir/Main.cpp.i

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-ultrasonic.dir/Main.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/sensor/ultrasonic/Main.cpp -o CMakeFiles/cvm-ultrasonic.dir/Main.cpp.s

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o.requires:

.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o.requires

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o.provides: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o.requires
	$(MAKE) -f cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/build.make cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o.provides.build
.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o.provides

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o.provides.build: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o


cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/flags.make
cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o: ../cvm/sensor/ultrasonic/Ultrasonic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o -c /home/ubuntu/cvm/cvm/sensor/ultrasonic/Ultrasonic.cpp

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/sensor/ultrasonic/Ultrasonic.cpp > CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.i

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/sensor/ultrasonic/Ultrasonic.cpp -o CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.s

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o.requires:

.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o.requires

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o.provides: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o.requires
	$(MAKE) -f cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/build.make cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o.provides.build
.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o.provides

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o.provides.build: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o


cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/flags.make
cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o: ../cvm/sensor/ultrasonic/UltrasonicConfig.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o -c /home/ubuntu/cvm/cvm/sensor/ultrasonic/UltrasonicConfig.cpp

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/sensor/ultrasonic/UltrasonicConfig.cpp > CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.i

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/sensor/ultrasonic/UltrasonicConfig.cpp -o CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.s

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o.requires:

.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o.requires

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o.provides: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o.requires
	$(MAKE) -f cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/build.make cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o.provides.build
.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o.provides

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o.provides.build: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o


# Object files for target cvm-ultrasonic
cvm__ultrasonic_OBJECTS = \
"CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o" \
"CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o" \
"CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o"

# External object files for target cvm-ultrasonic
cvm__ultrasonic_EXTERNAL_OBJECTS =

../bin/cvm-ultrasonic: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o
../bin/cvm-ultrasonic: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o
../bin/cvm-ultrasonic: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o
../bin/cvm-ultrasonic: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/build.make
../bin/cvm-ultrasonic: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../../../../bin/cvm-ultrasonic"
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cvm-ultrasonic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/build: ../bin/cvm-ultrasonic

.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/build

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/requires: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Main.cpp.o.requires
cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/requires: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/Ultrasonic.cpp.o.requires
cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/requires: cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/UltrasonicConfig.cpp.o.requires

.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/requires

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/clean:
	cd /home/ubuntu/cvm/build/cvm/sensor/ultrasonic && $(CMAKE_COMMAND) -P CMakeFiles/cvm-ultrasonic.dir/cmake_clean.cmake
.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/clean

cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/depend:
	cd /home/ubuntu/cvm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/cvm /home/ubuntu/cvm/cvm/sensor/ultrasonic /home/ubuntu/cvm/build /home/ubuntu/cvm/build/cvm/sensor/ultrasonic /home/ubuntu/cvm/build/cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cvm/sensor/ultrasonic/CMakeFiles/cvm-ultrasonic.dir/depend

