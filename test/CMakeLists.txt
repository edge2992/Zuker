cmake_minimum_required(VERSION 3.13)

include(${PROJECT_SOURCE_DIR}/cmake/DownloadProject/DownloadProject.cmake)
download_project(PROJ googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG master
  UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

add_executable(Test_zuker test_zuker.cpp)

target_link_libraries(Test_zuker zuker gtest gtest_main pthread)
include_directories(${PROJECT_SOURCE_DIR}/src)

target_compile_features(Test_zuker PUBLIC cxx_std_11)

include(GoogleTest)
gtest_add_tests(TARGET Test_zuker)
