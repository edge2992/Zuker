cmake_minimum_required(VERSION 3.13)
# add_library(zuker STATIC zuker.cpp traceback.cpp energy.cpp rna_seq.cpp)
add_library(zuker STATIC zuker.cpp traceback.cpp energy.cpp)
add_library(rna STATIC rna_seq.cpp)

add_executable(demo main.cc)
target_link_libraries(demo zuker rna)
# target_link_libraries(demo my_math)
