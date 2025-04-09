cmake_minimum_required(VERSION 3.22)

project(tst_viasyncworker)

#include(CodeCoverage)
include(CTest)

if(PROJECT_IS_TOP_LEVEL)
    if(NOT DEFINED UNITY_ROOT_PATH)
        set(UNITY_ROOT_PATH "../unity")
    endif()

    if(NOT DEFINED GTEST_ROOT_PATH)
        set(GTEST_ROOT_PATH "../gtest")
    endif()


    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/modules/unity)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/modules/gtest)
    # Set as executable
    add_subdirectory(${UNITY_ROOT_PATH} ${CMAKE_BINARY_DIR}/modules/unity)
    add_subdirectory(${GTEST_ROOT_PATH} ${CMAKE_BINARY_DIR}/modules/gtest)
endif()

# Add core subdir
add_subdirectory(core)

add_executable(tst_viasyncworker)
enable_testing()

# Add key executable block
target_sources(tst_viasyncworker PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tests/main/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_viasyncworker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_viduplexqueue.cpp
)

# Add key include paths
target_include_directories(tst_viasyncworker PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/core/src/inc
    ${CMAKE_CURRENT_LIST_DIR}/tests/mock
    ${UNITY_ROOT_PATH}/src
    ${UNITY_ROOT_PATH}/extras/fixture/src
    ${UNITY_ROOT_PATH}/extras/memory/src
    ${GTEST_ROOT_PATH}/googlemock/include
)

# Compilation definition information
target_compile_definitions(tst_viasyncworker PUBLIC
    #WIN32
    #_DEBUG
    #CONSOLE
)

# Compiler options
target_compile_options(tst_viasyncworker PRIVATE
    -g
    -fprofile-arcs 
    -ftest-coverage
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(
  tst_viasyncworker viasyncworker unity gmock -lgcov -fprofile-arcs -ftest-coverage -pthread)

add_test(NAME ViAsyncWorkerTest COMMAND tst_viasyncworker "--gtest_filter=ViAsyncWorkerTest.*")
add_test(NAME ViDuplexQueueTest COMMAND tst_viasyncworker "--gtest_filter=ViDuplexQueueTest.*")
