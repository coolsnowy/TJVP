# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/coolsnowy/Desktop/CVMBaic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug

# Include any dependencies generated for this target.
include cvm/sensor/logger/CMakeFiles/cvm-player.dir/depend.make

# Include the progress variables for this target.
include cvm/sensor/logger/CMakeFiles/cvm-player.dir/progress.make

# Include the compile flags for this target's objects.
include cvm/sensor/logger/CMakeFiles/cvm-player.dir/flags.make

cvm/sensor/logger/CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.o: cvm/sensor/logger/CMakeFiles/cvm-player.dir/flags.make
cvm/sensor/logger/CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.o: ../cvm/sensor/logger/LcmLogplayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cvm/sensor/logger/CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.o"
	cd /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug/cvm/sensor/logger && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.o -c /Users/coolsnowy/Desktop/CVMBaic/cvm/sensor/logger/LcmLogplayer.cpp

cvm/sensor/logger/CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.i"
	cd /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug/cvm/sensor/logger && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/coolsnowy/Desktop/CVMBaic/cvm/sensor/logger/LcmLogplayer.cpp > CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.i

cvm/sensor/logger/CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.s"
	cd /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug/cvm/sensor/logger && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/coolsnowy/Desktop/CVMBaic/cvm/sensor/logger/LcmLogplayer.cpp -o CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.s

# Object files for target cvm-player
cvm__player_OBJECTS = \
"CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.o"

# External object files for target cvm-player
cvm__player_EXTERNAL_OBJECTS =

../bin/cvm-player: cvm/sensor/logger/CMakeFiles/cvm-player.dir/LcmLogplayer.cpp.o
../bin/cvm-player: cvm/sensor/logger/CMakeFiles/cvm-player.dir/build.make
../bin/cvm-player: ../lib/libcvm.a
../bin/cvm-player: cvm/sensor/logger/CMakeFiles/cvm-player.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../bin/cvm-player"
	cd /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug/cvm/sensor/logger && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cvm-player.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cvm/sensor/logger/CMakeFiles/cvm-player.dir/build: ../bin/cvm-player

.PHONY : cvm/sensor/logger/CMakeFiles/cvm-player.dir/build

cvm/sensor/logger/CMakeFiles/cvm-player.dir/clean:
	cd /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug/cvm/sensor/logger && $(CMAKE_COMMAND) -P CMakeFiles/cvm-player.dir/cmake_clean.cmake
.PHONY : cvm/sensor/logger/CMakeFiles/cvm-player.dir/clean

cvm/sensor/logger/CMakeFiles/cvm-player.dir/depend:
	cd /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/coolsnowy/Desktop/CVMBaic /Users/coolsnowy/Desktop/CVMBaic/cvm/sensor/logger /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug/cvm/sensor/logger /Users/coolsnowy/Desktop/CVMBaic/cmake-build-debug/cvm/sensor/logger/CMakeFiles/cvm-player.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cvm/sensor/logger/CMakeFiles/cvm-player.dir/depend

