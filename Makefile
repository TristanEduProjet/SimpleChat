# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /root/SimpleChat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/SimpleChat

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /root/SimpleChat/CMakeFiles /root/SimpleChat/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /root/SimpleChat/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named schatCli

# Build rule for target.
schatCli: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 schatCli
.PHONY : schatCli

# fast build rule for target.
schatCli/fast:
	$(MAKE) -f CMakeFiles/schatCli.dir/build.make CMakeFiles/schatCli.dir/build
.PHONY : schatCli/fast

#=============================================================================
# Target rules for targets named SChat

# Build rule for target.
SChat: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 SChat
.PHONY : SChat

# fast build rule for target.
SChat/fast:
	$(MAKE) -f CMakeFiles/SChat.dir/build.make CMakeFiles/SChat.dir/build
.PHONY : SChat/fast

#=============================================================================
# Target rules for targets named schatSrv

# Build rule for target.
schatSrv: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 schatSrv
.PHONY : schatSrv

# fast build rule for target.
schatSrv/fast:
	$(MAKE) -f CMakeFiles/schatSrv.dir/build.make CMakeFiles/schatSrv.dir/build
.PHONY : schatSrv/fast

client/main.o: client/main.cpp.o

.PHONY : client/main.o

# target to build an object file
client/main.cpp.o:
	$(MAKE) -f CMakeFiles/schatCli.dir/build.make CMakeFiles/schatCli.dir/client/main.cpp.o
.PHONY : client/main.cpp.o

client/main.i: client/main.cpp.i

.PHONY : client/main.i

# target to preprocess a source file
client/main.cpp.i:
	$(MAKE) -f CMakeFiles/schatCli.dir/build.make CMakeFiles/schatCli.dir/client/main.cpp.i
.PHONY : client/main.cpp.i

client/main.s: client/main.cpp.s

.PHONY : client/main.s

# target to generate assembly for a file
client/main.cpp.s:
	$(MAKE) -f CMakeFiles/schatCli.dir/build.make CMakeFiles/schatCli.dir/client/main.cpp.s
.PHONY : client/main.cpp.s

common/sample.o: common/sample.cpp.o

.PHONY : common/sample.o

# target to build an object file
common/sample.cpp.o:
	$(MAKE) -f CMakeFiles/SChat.dir/build.make CMakeFiles/SChat.dir/common/sample.cpp.o
.PHONY : common/sample.cpp.o

common/sample.i: common/sample.cpp.i

.PHONY : common/sample.i

# target to preprocess a source file
common/sample.cpp.i:
	$(MAKE) -f CMakeFiles/SChat.dir/build.make CMakeFiles/SChat.dir/common/sample.cpp.i
.PHONY : common/sample.cpp.i

common/sample.s: common/sample.cpp.s

.PHONY : common/sample.s

# target to generate assembly for a file
common/sample.cpp.s:
	$(MAKE) -f CMakeFiles/SChat.dir/build.make CMakeFiles/SChat.dir/common/sample.cpp.s
.PHONY : common/sample.cpp.s

server/main.o: server/main.cpp.o

.PHONY : server/main.o

# target to build an object file
server/main.cpp.o:
	$(MAKE) -f CMakeFiles/schatSrv.dir/build.make CMakeFiles/schatSrv.dir/server/main.cpp.o
.PHONY : server/main.cpp.o

server/main.i: server/main.cpp.i

.PHONY : server/main.i

# target to preprocess a source file
server/main.cpp.i:
	$(MAKE) -f CMakeFiles/schatSrv.dir/build.make CMakeFiles/schatSrv.dir/server/main.cpp.i
.PHONY : server/main.cpp.i

server/main.s: server/main.cpp.s

.PHONY : server/main.s

# target to generate assembly for a file
server/main.cpp.s:
	$(MAKE) -f CMakeFiles/schatSrv.dir/build.make CMakeFiles/schatSrv.dir/server/main.cpp.s
.PHONY : server/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... schatCli"
	@echo "... SChat"
	@echo "... schatSrv"
	@echo "... client/main.o"
	@echo "... client/main.i"
	@echo "... client/main.s"
	@echo "... common/sample.o"
	@echo "... common/sample.i"
	@echo "... common/sample.s"
	@echo "... server/main.o"
	@echo "... server/main.i"
	@echo "... server/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

