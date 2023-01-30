cmake_minimum_required(VERSION 3.1)
project(frameDetect CXX C)  # 这里可以不写CXX和C，但不能只写一个，否则只会编译指定语言

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

list(APPEND FRAME_DETECT_SRCS
"frameDetect.cc"
"frameDetect.h"
"greenDetect.cc"
"greenDetect.h"
"blackDetect.cc"
"blackDetect.h")

add_library(frameDetect ${FRAME_DETECT_SRCS})
