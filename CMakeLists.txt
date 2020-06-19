cmake_minimum_required(VERSION 3.13)
project (ZUKER)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME ZukerTest COMMAND Test_zuker)

