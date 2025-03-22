cmake_minimum_required(VERSION 3.22)

project(viasyncworker)

# Debug message
message("Entering ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")

# Register core library
add_library(viasyncworker INTERFACE)

target_sources(viasyncworker PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/viasyncworker.cpp)

target_include_directories(viasyncworker INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/inc)
