cmake_minimum_required(VERSION 3.10)
project(MemoryManager)
set(CMAKE_CXX_STANDARD 14)

# Add Google Test to the build.
add_subdirectory(googletest)

# Enable CMake's testing functionality
enable_testing()

# Specify the executable for the main application
add_executable(MemoryManager main.cpp
        SegmentedFreeListAllocator.h
        MemoryBlock.h
        IMemoryAllocator.h)

# Define test executable.
add_executable(MemoryManagerTests tests/SegmentedFreeListAllocatorTest.cpp
        SegmentedFreeListAllocator.h
        IMemoryAllocator.h)

# Include Google Test headers
target_include_directories(MemoryManagerTests PRIVATE ${PROJECT_SOURCE_DIR}/googletest/googletest/include)

# Link Google Test to your test executable.
target_link_libraries(MemoryManagerTests gtest gtest_main)

# Add the tests to be run by CMake's testing system.
add_test(NAME MemoryManagerTest COMMAND MemoryManagerTests)
