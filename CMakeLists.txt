cmake_minimum_required(VERSION 3.27)
project(kaleidoscope VERSION 0.1.0 LANGUAGES C CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(kaleidoscope main.cpp include/Globals.cpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(MPFR REQUIRED)
message(STATUS "Found MPFR: ${MPFR_FOUND}")
target_link_libraries(kaleidoscope "${MPFR_LIBRARIES}")