cmake_minimum_required(VERSION 3.15)
project(CppExamples LANGUAGES CXX)

enable_testing()

set(SUBDIRS 
	C++11
	C++17
   )

foreach(SUBDIR ${SUBDIRS})
    add_subdirectory(${SUBDIR})
endforeach()

