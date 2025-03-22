cmake_minimum_required(VERSION 3.22)

project(tst_viasyncworker)

#include(CodeCoverage)
include(CTest)

if(PROJECT_IS_TOP_LEVEL)
# Set as executable
add_subdirectory(${UNITY_ROOT_PATH} ${${EXECUTABLE}_BINARY_DIR}/modules/gtest)
endif()

# Add core subdir
add_subdirectory(core)

add_executable(tst_viasyncworker)
enable_testing()

# Add key executable block
target_sources(tst_viasyncworker PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tests/main/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_viasyncworker.cpp
)

# Add key include paths
target_include_directories(tst_viasyncworker PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/core/src/inc
    ${UNITY_ROOT_PATH}/src
    ${UNITY_ROOT_PATH}/extras/fixture/src
    ${UNITY_ROOT_PATH}/extras/memory/src
)

# Compilation definition information
target_compile_definitions(tst_viasyncworker PUBLIC
    WIN32
    _DEBUG
    CONSOLE
)

# Compiler options
target_compile_options(tst_viasyncworker PRIVATE
    -g
    --coverage
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(
  tst_viasyncworker viasyncworker unity -g -coverage -lgcov)

#add_test(NAME VIHCSR04_Init COMMAND tst_vibuttonctrl "--gtest_filter=VIHCSR04_Init.*")
