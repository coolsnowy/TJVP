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
include cvm/sensor/logger/CMakeFiles/cvm-logger.dir/depend.make

# Include the progress variables for this target.
include cvm/sensor/logger/CMakeFiles/cvm-logger.dir/progress.make

# Include the compile flags for this target's objects.
include cvm/sensor/logger/CMakeFiles/cvm-logger.dir/flags.make

cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o: cvm/sensor/logger/CMakeFiles/cvm-logger.dir/flags.make
cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o: ../cvm/sensor/logger/LcmLogger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o"
	cd /home/ubuntu/cvm/build/cvm/sensor/logger && arm-linux-gnueabihf-g++-4.8   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o -c /home/ubuntu/cvm/cvm/sensor/logger/LcmLogger.cpp

cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-logger.dir/LcmLogger.cpp.i"
	cd /home/ubuntu/cvm/build/cvm/sensor/logger && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/cvm/cvm/sensor/logger/LcmLogger.cpp > CMakeFiles/cvm-logger.dir/LcmLogger.cpp.i

cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-logger.dir/LcmLogger.cpp.s"
	cd /home/ubuntu/cvm/build/cvm/sensor/logger && arm-linux-gnueabihf-g++-4.8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/cvm/cvm/sensor/logger/LcmLogger.cpp -o CMakeFiles/cvm-logger.dir/LcmLogger.cpp.s

cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o.requires:

.PHONY : cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o.requires

cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o.provides: cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o.requires
	$(MAKE) -f cvm/sensor/logger/CMakeFiles/cvm-logger.dir/build.make cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o.provides.build
.PHONY : cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o.provides

cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o.provides.build: cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o


# Object files for target cvm-logger
cvm__logger_OBJECTS = \
"CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o"

# External object files for target cvm-logger
cvm__logger_EXTERNAL_OBJECTS =

../bin/cvm-logger: cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o
../bin/cvm-logger: cvm/sensor/logger/CMakeFiles/cvm-logger.dir/build.make
../bin/cvm-logger: ../lib/libcvm.a
../bin/cvm-logger: cvm/sensor/logger/CMakeFiles/cvm-logger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/cvm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../bin/cvm-logger"
	cd /home/ubuntu/cvm/build/cvm/sensor/logger && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cvm-logger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cvm/sensor/logger/CMakeFiles/cvm-logger.dir/build: ../bin/cvm-logger

.PHONY : cvm/sensor/logger/CMakeFiles/cvm-logger.dir/build

cvm/sensor/logger/CMakeFiles/cvm-logger.dir/requires: cvm/sensor/logger/CMakeFiles/cvm-logger.dir/LcmLogger.cpp.o.requires

.PHONY : cvm/sensor/logger/CMakeFiles/cvm-logger.dir/requires

cvm/sensor/logger/CMakeFiles/cvm-logger.dir/clean:
	cd /home/ubuntu/cvm/build/cvm/sensor/logger && $(CMAKE_COMMAND) -P CMakeFiles/cvm-logger.dir/cmake_clean.cmake
.PHONY : cvm/sensor/logger/CMakeFiles/cvm-logger.dir/clean

cvm/sensor/logger/CMakeFiles/cvm-logger.dir/depend:
	cd /home/ubuntu/cvm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/cvm /home/ubuntu/cvm/cvm/sensor/logger /home/ubuntu/cvm/build /home/ubuntu/cvm/build/cvm/sensor/logger /home/ubuntu/cvm/build/cvm/sensor/logger/CMakeFiles/cvm-logger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cvm/sensor/logger/CMakeFiles/cvm-logger.dir/depend

