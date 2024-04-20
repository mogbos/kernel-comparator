cmake_minimum_required(VERSION 3.0)
project(kernel-comparator)

# Add executable target
file(GLOB SOURCES "src/*.cpp")

add_executable(kernel-comparator
    ${SOURCES}
)

# Include directories
target_include_directories(kernel-comparator PRIVATE
    include
)

# Optionally, set C++ standard
set_property(TARGET kernel-comparator PROPERTY CXX_STANDARD 11)
