cmake_minimum_required(VERSION 3.10)

project(UPI)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
# file(GLOB_RECURSE SOURCES "src/*.cpp")
set(SOURCES
    src/main.cpp
    src/cli.cpp
    src/filesystem_scanner.cpp
    src/conflict_analyzer.cpp
    src/report_generator.cpp
    src/package_manager/package_manager_base.cpp
    src/package_manager/dpkg_adapter.cpp
    src/package_manager/rpm_adapter.cpp
    src/package_manager/dnf_adapter.cpp
    src/package_manager/flatpak_adapter.cpp
    src/package_manager/snap_adapter.cpp
    src/package_manager/pip_adapter.cpp
)

# Executable
add_executable(upi ${SOURCES})

# Google Test setup
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test executable
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(upi_tests 
                ${TEST_SOURCES}
                ${SOURCES})

# Link Google Test libraries
target_link_libraries(upi_tests ${GTEST_LIBRARIES} pthread)

# Add tests
add_test(NAME AllTests COMMAND upi_tests)

# Link libraries (if needed)
# target_link_libraries(upi ...)
