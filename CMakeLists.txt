cmake_minimum_required(VERSION 3.16)
project(Navek)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp HttpHeader.cpp HttpHeader.h HttpHeaderParser.cpp HttpHeaderParser.h ExecutionTimer.h)

add_executable(Navek ${SOURCE_FILES})
