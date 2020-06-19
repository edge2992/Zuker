cmake_minimum_required(VERSION 3.13)
project (MYTEST)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME EnergyTest COMMAND Test_energy)
add_test(NAME ZukerTest COMMAND Test_zuker)

