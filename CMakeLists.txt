cmake_minimum_required(VERSION 3.17)
project(OptMethods)

set(CMAKE_CXX_STANDARD 17)

add_executable(OptMethods main.cpp optimizing_method.h dichotomy_method.h golden_ratio_method.h fibonacci_method.h parabola_method.h brent_method.h steepest_descent.h gradient_descent.h conjugate_gradients.h diag_form.h optimizable.h utils.h)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-Ofast")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")