# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tyjo/projects/sop/ns3/NS3/NS3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tyjo/projects/sop/ns3/NS3/NS3

# Include any dependencies generated for this target.
include scratch/CMakeFiles/wifi-simple-adhoc.dir/depend.make

# Include the progress variables for this target.
include scratch/CMakeFiles/wifi-simple-adhoc.dir/progress.make

# Include the compile flags for this target's objects.
include scratch/CMakeFiles/wifi-simple-adhoc.dir/flags.make

scratch/CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.o: scratch/CMakeFiles/wifi-simple-adhoc.dir/flags.make
scratch/CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.o: scratch/wifi-simple-adhoc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tyjo/projects/sop/ns3/NS3/NS3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object scratch/CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.o"
	cd /home/tyjo/projects/sop/ns3/NS3/NS3/scratch && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.o -c /home/tyjo/projects/sop/ns3/NS3/NS3/scratch/wifi-simple-adhoc.cc

scratch/CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.i"
	cd /home/tyjo/projects/sop/ns3/NS3/NS3/scratch && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tyjo/projects/sop/ns3/NS3/NS3/scratch/wifi-simple-adhoc.cc > CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.i

scratch/CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.s"
	cd /home/tyjo/projects/sop/ns3/NS3/NS3/scratch && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tyjo/projects/sop/ns3/NS3/NS3/scratch/wifi-simple-adhoc.cc -o CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.s

# Object files for target wifi-simple-adhoc
wifi__simple__adhoc_OBJECTS = \
"CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.o"

# External object files for target wifi-simple-adhoc
wifi__simple__adhoc_EXTERNAL_OBJECTS = \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/csma-system-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tc/fq-codel-queue-disc-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tc/pfifo-fast-queue-disc-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-cwnd-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-interop-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-loss-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-no-delay-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-socket-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-state-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/nsctcp-loss-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-socket-writer.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3wifi/wifi-interference-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3wifi/wifi-msdu-aggregator-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/ns3wifi/wifi-ac-mapping-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/traced/traced-callback-typedef-test-suite.cc.o" \
"/home/tyjo/projects/sop/ns3/NS3/NS3/src/test/CMakeFiles/ns3.29-test-rel.dir/traced/traced-value-callback-typedef-test-suite.cc.o"

build/bin/wifi-simple-adhoc: scratch/CMakeFiles/wifi-simple-adhoc.dir/wifi-simple-adhoc.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/csma-system-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tc/fq-codel-queue-disc-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tc/pfifo-fast-queue-disc-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-cwnd-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-interop-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-loss-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-no-delay-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-socket-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-state-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/nsctcp-loss-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3tcp/ns3tcp-socket-writer.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3wifi/wifi-interference-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3wifi/wifi-msdu-aggregator-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/ns3wifi/wifi-ac-mapping-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/traced/traced-callback-typedef-test-suite.cc.o
build/bin/wifi-simple-adhoc: src/test/CMakeFiles/ns3.29-test-rel.dir/traced/traced-value-callback-typedef-test-suite.cc.o
build/bin/wifi-simple-adhoc: scratch/CMakeFiles/wifi-simple-adhoc.dir/build.make
build/bin/wifi-simple-adhoc: build/lib/libns3.29-aodv-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-brite-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-click-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-csma-layout-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-dsdv-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-dsr-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-fd-net-device-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-flow-monitor-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-internet-apps-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-mesh-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-netanim-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-nix-vector-routing-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-olsr-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-point-to-point-layout-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-sixlowpan-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-topology-read-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-uan-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-wave-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-wifi-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-wimax-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-contrib-haraldott-rel.so
build/bin/wifi-simple-adhoc: build/lib/libbrite.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-lr-wpan-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-lte-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-applications-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-buildings-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-config-store-rel.so
build/bin/wifi-simple-adhoc: /usr/lib/x86_64-linux-gnu/libxml2.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-csma-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-virtual-net-device-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-energy-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-spectrum-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-antenna-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-propagation-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-mobility-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-point-to-point-rel.so
build/bin/wifi-simple-adhoc: /usr/lib/x86_64-linux-gnu/libpcre2-8.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-internet-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-bridge-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-mpi-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-traffic-control-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-network-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-stats-rel.so
build/bin/wifi-simple-adhoc: build/lib/libns3.29-core-rel.so
build/bin/wifi-simple-adhoc: /usr/lib/x86_64-linux-gnu/librt.so
build/bin/wifi-simple-adhoc: scratch/CMakeFiles/wifi-simple-adhoc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tyjo/projects/sop/ns3/NS3/NS3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../build/bin/wifi-simple-adhoc"
	cd /home/tyjo/projects/sop/ns3/NS3/NS3/scratch && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wifi-simple-adhoc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
scratch/CMakeFiles/wifi-simple-adhoc.dir/build: build/bin/wifi-simple-adhoc

.PHONY : scratch/CMakeFiles/wifi-simple-adhoc.dir/build

scratch/CMakeFiles/wifi-simple-adhoc.dir/clean:
	cd /home/tyjo/projects/sop/ns3/NS3/NS3/scratch && $(CMAKE_COMMAND) -P CMakeFiles/wifi-simple-adhoc.dir/cmake_clean.cmake
.PHONY : scratch/CMakeFiles/wifi-simple-adhoc.dir/clean

scratch/CMakeFiles/wifi-simple-adhoc.dir/depend:
	cd /home/tyjo/projects/sop/ns3/NS3/NS3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tyjo/projects/sop/ns3/NS3/NS3 /home/tyjo/projects/sop/ns3/NS3/NS3/scratch /home/tyjo/projects/sop/ns3/NS3/NS3 /home/tyjo/projects/sop/ns3/NS3/NS3/scratch /home/tyjo/projects/sop/ns3/NS3/NS3/scratch/CMakeFiles/wifi-simple-adhoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : scratch/CMakeFiles/wifi-simple-adhoc.dir/depend

