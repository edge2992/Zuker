cmake_minimum_required(VERSION 3.13)
# add_library(zuker STATIC zuker.cpp traceback.cpp energy.cpp rna_seq.cpp)

include(${PROJECT_SOURCE_DIR}/cmake/DownloadProject/DownloadProject.cmake)
download_project(PROJ spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.x
  UPDATE_DISCONNECTED 1
)

add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
add_library(zuker STATIC zuker.cpp traceback.cpp energy.cpp)
add_library(rna STATIC rna_seq.cpp)
target_link_libraries(zuker spdlog)
target_link_libraries(rna spdlog)

add_executable(demo main.cc)
target_link_libraries(demo zuker rna spdlog)
# target_link_libraries(demo my_math)
