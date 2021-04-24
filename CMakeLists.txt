cmake_minimum_required(VERSION 3.17)
project(OptMethods)

set(CMAKE_CXX_STANDARD 17)

add_executable(OptMethods main.cpp optimizing_method.h steps_printer.h dichotomy_method.h golden_ratio_method.h fibonacci_method.h parabola_method.h brent_method.h steepest_descent.h)