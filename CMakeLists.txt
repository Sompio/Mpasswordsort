cmake_minimum_required(VERSION 3.6)
project(ou1)

set(CMAKE_C_FLAGS "-std=c11")

set(SOURCE_FILES
        list.c
        list.h
        mpasswdsort.c
        mpasswdsort.h)

add_executable(ou1 ${SOURCE_FILES} mpasswdsort.c)