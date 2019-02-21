cmake_minimum_required(VERSION 3.5.1)
project(PolyDataStruct)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")


FILE(GLOB SOURCE_FILES *.cpp)
FILE(GLOB HEADER_FILES *.h)

add_executable(exec ${HEADER_FILES} ${SOURCE_FILES})
