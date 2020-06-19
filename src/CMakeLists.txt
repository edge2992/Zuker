cmake_minimum_required(VERSION 3.13)
add_library(energy STATIC energy.cpp)
add_library(zuker STATIC zuker.cpp)

add_executable(demo main.cc)
target_link_libraries(demo zuker)
# target_link_libraries(demo my_math)
