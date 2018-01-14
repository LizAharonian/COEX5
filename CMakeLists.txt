cmake_minimum_required(VERSION 3.8)
project(COEX5)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES myfunction.c readBMP.c readBMP.h showBMP.c writeBMP.c writeBMP.h sapir.c)
add_executable(COEX5 ${SOURCE_FILES})