# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/anon/Code/whisper-protocol

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anon/Code/whisper-protocol

# Include any dependencies generated for this target.
include CMakeFiles/whisper_protocols.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/whisper_protocols.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/whisper_protocols.dir/flags.make

CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o: CMakeFiles/whisper_protocols.dir/flags.make
CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o: src/obj/wpmessage.pb-c.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anon/Code/whisper-protocol/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o   -c /home/anon/Code/whisper-protocol/src/obj/wpmessage.pb-c.c

CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/anon/Code/whisper-protocol/src/obj/wpmessage.pb-c.c > CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.i

CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/anon/Code/whisper-protocol/src/obj/wpmessage.pb-c.c -o CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.s

CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o.requires:
.PHONY : CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o.requires

CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o.provides: CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o.requires
	$(MAKE) -f CMakeFiles/whisper_protocols.dir/build.make CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o.provides.build
.PHONY : CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o.provides

CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o.provides.build: CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o

CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o: CMakeFiles/whisper_protocols.dir/flags.make
CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o: src/protocol/wpprotocol.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anon/Code/whisper-protocol/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o   -c /home/anon/Code/whisper-protocol/src/protocol/wpprotocol.c

CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/anon/Code/whisper-protocol/src/protocol/wpprotocol.c > CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.i

CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/anon/Code/whisper-protocol/src/protocol/wpprotocol.c -o CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.s

CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o.requires:
.PHONY : CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o.requires

CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o.provides: CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o.requires
	$(MAKE) -f CMakeFiles/whisper_protocols.dir/build.make CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o.provides.build
.PHONY : CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o.provides

CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o.provides.build: CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o

# Object files for target whisper_protocols
whisper_protocols_OBJECTS = \
"CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o" \
"CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o"

# External object files for target whisper_protocols
whisper_protocols_EXTERNAL_OBJECTS =

libwhisper_protocols.so: CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o
libwhisper_protocols.so: CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o
libwhisper_protocols.so: CMakeFiles/whisper_protocols.dir/build.make
libwhisper_protocols.so: CMakeFiles/whisper_protocols.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libwhisper_protocols.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/whisper_protocols.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/whisper_protocols.dir/build: libwhisper_protocols.so
.PHONY : CMakeFiles/whisper_protocols.dir/build

CMakeFiles/whisper_protocols.dir/requires: CMakeFiles/whisper_protocols.dir/src/obj/wpmessage.pb-c.c.o.requires
CMakeFiles/whisper_protocols.dir/requires: CMakeFiles/whisper_protocols.dir/src/protocol/wpprotocol.c.o.requires
.PHONY : CMakeFiles/whisper_protocols.dir/requires

CMakeFiles/whisper_protocols.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/whisper_protocols.dir/cmake_clean.cmake
.PHONY : CMakeFiles/whisper_protocols.dir/clean

CMakeFiles/whisper_protocols.dir/depend:
	cd /home/anon/Code/whisper-protocol && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anon/Code/whisper-protocol /home/anon/Code/whisper-protocol /home/anon/Code/whisper-protocol /home/anon/Code/whisper-protocol /home/anon/Code/whisper-protocol/CMakeFiles/whisper_protocols.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/whisper_protocols.dir/depend

