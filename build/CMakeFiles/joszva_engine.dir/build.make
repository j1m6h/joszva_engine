# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_SOURCE_DIR = /home/joshua/Desktop/joszva_engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joshua/Desktop/joszva_engine/build

# Include any dependencies generated for this target.
include CMakeFiles/joszva_engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/joszva_engine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/joszva_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/joszva_engine.dir/flags.make

CMakeFiles/joszva_engine.dir/src/main.cpp.o: CMakeFiles/joszva_engine.dir/flags.make
CMakeFiles/joszva_engine.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/joszva_engine.dir/src/main.cpp.o: CMakeFiles/joszva_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/joszva_engine.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joszva_engine.dir/src/main.cpp.o -MF CMakeFiles/joszva_engine.dir/src/main.cpp.o.d -o CMakeFiles/joszva_engine.dir/src/main.cpp.o -c /home/joshua/Desktop/joszva_engine/src/main.cpp

CMakeFiles/joszva_engine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joszva_engine.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/Desktop/joszva_engine/src/main.cpp > CMakeFiles/joszva_engine.dir/src/main.cpp.i

CMakeFiles/joszva_engine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joszva_engine.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/Desktop/joszva_engine/src/main.cpp -o CMakeFiles/joszva_engine.dir/src/main.cpp.s

CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.o: CMakeFiles/joszva_engine.dir/flags.make
CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.o: ../src/renderer/vulkan/vk_descriptor_pool.cpp
CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.o: CMakeFiles/joszva_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.o -MF CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.o.d -o CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.o -c /home/joshua/Desktop/joszva_engine/src/renderer/vulkan/vk_descriptor_pool.cpp

CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/Desktop/joszva_engine/src/renderer/vulkan/vk_descriptor_pool.cpp > CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.i

CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/Desktop/joszva_engine/src/renderer/vulkan/vk_descriptor_pool.cpp -o CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.s

CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.o: CMakeFiles/joszva_engine.dir/flags.make
CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.o: ../src/renderer/vulkan/vk_device.cpp
CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.o: CMakeFiles/joszva_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.o -MF CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.o.d -o CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.o -c /home/joshua/Desktop/joszva_engine/src/renderer/vulkan/vk_device.cpp

CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/Desktop/joszva_engine/src/renderer/vulkan/vk_device.cpp > CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.i

CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/Desktop/joszva_engine/src/renderer/vulkan/vk_device.cpp -o CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.s

CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.o: CMakeFiles/joszva_engine.dir/flags.make
CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.o: ../src/renderer/vulkan/vk_instance.cpp
CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.o: CMakeFiles/joszva_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.o -MF CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.o.d -o CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.o -c /home/joshua/Desktop/joszva_engine/src/renderer/vulkan/vk_instance.cpp

CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/Desktop/joszva_engine/src/renderer/vulkan/vk_instance.cpp > CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.i

CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/Desktop/joszva_engine/src/renderer/vulkan/vk_instance.cpp -o CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.s

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.o: CMakeFiles/joszva_engine.dir/flags.make
CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.o: ../vendor/imgui/imgui.cpp
CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.o: CMakeFiles/joszva_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.o -MF CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.o.d -o CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.o -c /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui.cpp

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui.cpp > CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.i

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui.cpp -o CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.s

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.o: CMakeFiles/joszva_engine.dir/flags.make
CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.o: ../vendor/imgui/imgui_draw.cpp
CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.o: CMakeFiles/joszva_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.o -MF CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.o.d -o CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.o -c /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui_draw.cpp

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui_draw.cpp > CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.i

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui_draw.cpp -o CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.s

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.o: CMakeFiles/joszva_engine.dir/flags.make
CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.o: ../vendor/imgui/imgui_tables.cpp
CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.o: CMakeFiles/joszva_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.o -MF CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.o.d -o CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.o -c /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui_tables.cpp

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui_tables.cpp > CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.i

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui_tables.cpp -o CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.s

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.o: CMakeFiles/joszva_engine.dir/flags.make
CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.o: ../vendor/imgui/imgui_widgets.cpp
CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.o: CMakeFiles/joszva_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.o -MF CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.o -c /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui_widgets.cpp

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui_widgets.cpp > CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.i

CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/Desktop/joszva_engine/vendor/imgui/imgui_widgets.cpp -o CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.s

CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.o: CMakeFiles/joszva_engine.dir/flags.make
CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.o: ../vendor/imgui/backends/imgui_impl_vulkan.cpp
CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.o: CMakeFiles/joszva_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.o -MF CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.o.d -o CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.o -c /home/joshua/Desktop/joszva_engine/vendor/imgui/backends/imgui_impl_vulkan.cpp

CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshua/Desktop/joszva_engine/vendor/imgui/backends/imgui_impl_vulkan.cpp > CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.i

CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshua/Desktop/joszva_engine/vendor/imgui/backends/imgui_impl_vulkan.cpp -o CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.s

# Object files for target joszva_engine
joszva_engine_OBJECTS = \
"CMakeFiles/joszva_engine.dir/src/main.cpp.o" \
"CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.o" \
"CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.o" \
"CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.o" \
"CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.o" \
"CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.o" \
"CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.o" \
"CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.o" \
"CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.o"

# External object files for target joszva_engine
joszva_engine_EXTERNAL_OBJECTS =

joszva_engine: CMakeFiles/joszva_engine.dir/src/main.cpp.o
joszva_engine: CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_descriptor_pool.cpp.o
joszva_engine: CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_device.cpp.o
joszva_engine: CMakeFiles/joszva_engine.dir/src/renderer/vulkan/vk_instance.cpp.o
joszva_engine: CMakeFiles/joszva_engine.dir/vendor/imgui/imgui.cpp.o
joszva_engine: CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_draw.cpp.o
joszva_engine: CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_tables.cpp.o
joszva_engine: CMakeFiles/joszva_engine.dir/vendor/imgui/imgui_widgets.cpp.o
joszva_engine: CMakeFiles/joszva_engine.dir/vendor/imgui/backends/imgui_impl_vulkan.cpp.o
joszva_engine: CMakeFiles/joszva_engine.dir/build.make
joszva_engine: /lib/libvulkan.so
joszva_engine: ../vendor/joszva_graphics/lib/libjoszva_graphics.so
joszva_engine: ../vendor/joszva_log/lib/libjoszva_log.so
joszva_engine: CMakeFiles/joszva_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joshua/Desktop/joszva_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable joszva_engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/joszva_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/joszva_engine.dir/build: joszva_engine
.PHONY : CMakeFiles/joszva_engine.dir/build

CMakeFiles/joszva_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/joszva_engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/joszva_engine.dir/clean

CMakeFiles/joszva_engine.dir/depend:
	cd /home/joshua/Desktop/joszva_engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joshua/Desktop/joszva_engine /home/joshua/Desktop/joszva_engine /home/joshua/Desktop/joszva_engine/build /home/joshua/Desktop/joszva_engine/build /home/joshua/Desktop/joszva_engine/build/CMakeFiles/joszva_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/joszva_engine.dir/depend
