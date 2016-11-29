cmake_minimum_required(VERSION 3.6)
project(themes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${YOUR_DIRECTORY})

set(SOURCE_FILES Date.cpp Date.h AcademicYear.cpp AcademicYear.h main.cpp Menu.cpp Menu.h Person.cpp Person.h Project.cpp Project.h utilities.h utilities.cpp
        Exceptions.h Theme.cpp Theme.h)
add_executable(themes ${SOURCE_FILES})