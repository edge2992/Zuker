cmake_minimum_required(VERSION 3.13)

include(${PROJECT_SOURCE_DIR}/cmake/DownloadProject/DownloadProject.cmake)
download_project(PROJ googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG master
  UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

add_executable(Test_energy test_energy.cpp)

target_link_libraries(Test_energy energy gtest gtest_main pthread)
include_directories(${PROJECT_SOURCE_DIR}/src)

target_compile_features(Test_energy PUBLIC cxx_std_11)

include(GoogleTest)
gtest_add_tests(TARGET Test_energy)


# set(CMAKE_RUNTIME_OUTPUIT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# set(GTEST_ROOT ~/temp/googletest/googletest/)

# include_directories(${GTEST_ROOT}/include/)

# link_directories(${GTEST_ROOT}/build/)

# add_executable(Test ${CMAKE_CURRENT_SOURCE_DIR}/test.cc)

# target_link_libraries(Test my_math gtest gtest_main pthread)


