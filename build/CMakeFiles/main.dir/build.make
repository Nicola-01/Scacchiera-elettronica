# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nicola/Documents/Progetto/Scacchiera-elettronica

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nicola/Documents/Progetto/Scacchiera-elettronica/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/Main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Main.cpp.o: ../src/Main.cpp
CMakeFiles/main.dir/src/Main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nicola/Documents/Progetto/Scacchiera-elettronica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/src/Main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Main.cpp.o -MF CMakeFiles/main.dir/src/Main.cpp.o.d -o CMakeFiles/main.dir/src/Main.cpp.o -c /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Main.cpp

CMakeFiles/main.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Main.cpp > CMakeFiles/main.dir/src/Main.cpp.i

CMakeFiles/main.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Main.cpp -o CMakeFiles/main.dir/src/Main.cpp.s

CMakeFiles/main.dir/src/Chessboard.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Chessboard.cpp.o: ../src/Chessboard.cpp
CMakeFiles/main.dir/src/Chessboard.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nicola/Documents/Progetto/Scacchiera-elettronica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/Chessboard.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Chessboard.cpp.o -MF CMakeFiles/main.dir/src/Chessboard.cpp.o.d -o CMakeFiles/main.dir/src/Chessboard.cpp.o -c /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Chessboard.cpp

CMakeFiles/main.dir/src/Chessboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Chessboard.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Chessboard.cpp > CMakeFiles/main.dir/src/Chessboard.cpp.i

CMakeFiles/main.dir/src/Chessboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Chessboard.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Chessboard.cpp -o CMakeFiles/main.dir/src/Chessboard.cpp.s

CMakeFiles/main.dir/src/Piece.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Piece.cpp.o: ../src/Piece.cpp
CMakeFiles/main.dir/src/Piece.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nicola/Documents/Progetto/Scacchiera-elettronica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/src/Piece.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Piece.cpp.o -MF CMakeFiles/main.dir/src/Piece.cpp.o.d -o CMakeFiles/main.dir/src/Piece.cpp.o -c /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Piece.cpp

CMakeFiles/main.dir/src/Piece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Piece.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Piece.cpp > CMakeFiles/main.dir/src/Piece.cpp.i

CMakeFiles/main.dir/src/Piece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Piece.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Piece.cpp -o CMakeFiles/main.dir/src/Piece.cpp.s

CMakeFiles/main.dir/src/Rules.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Rules.cpp.o: ../src/Rules.cpp
CMakeFiles/main.dir/src/Rules.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nicola/Documents/Progetto/Scacchiera-elettronica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/src/Rules.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Rules.cpp.o -MF CMakeFiles/main.dir/src/Rules.cpp.o.d -o CMakeFiles/main.dir/src/Rules.cpp.o -c /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Rules.cpp

CMakeFiles/main.dir/src/Rules.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Rules.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Rules.cpp > CMakeFiles/main.dir/src/Rules.cpp.i

CMakeFiles/main.dir/src/Rules.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Rules.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nicola/Documents/Progetto/Scacchiera-elettronica/src/Rules.cpp -o CMakeFiles/main.dir/src/Rules.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/Main.cpp.o" \
"CMakeFiles/main.dir/src/Chessboard.cpp.o" \
"CMakeFiles/main.dir/src/Piece.cpp.o" \
"CMakeFiles/main.dir/src/Rules.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/src/Main.cpp.o
main: CMakeFiles/main.dir/src/Chessboard.cpp.o
main: CMakeFiles/main.dir/src/Piece.cpp.o
main: CMakeFiles/main.dir/src/Rules.cpp.o
main: CMakeFiles/main.dir/build.make
main: liblibs.a
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nicola/Documents/Progetto/Scacchiera-elettronica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/nicola/Documents/Progetto/Scacchiera-elettronica/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nicola/Documents/Progetto/Scacchiera-elettronica /home/nicola/Documents/Progetto/Scacchiera-elettronica /home/nicola/Documents/Progetto/Scacchiera-elettronica/build /home/nicola/Documents/Progetto/Scacchiera-elettronica/build /home/nicola/Documents/Progetto/Scacchiera-elettronica/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

