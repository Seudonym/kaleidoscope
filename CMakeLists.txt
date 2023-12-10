cmake_minimum_required(VERSION 3.27)
project(kaleidoscope VERSION 0.1.0 LANGUAGES C CXX)

add_executable(kaleidoscope main.cpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(MPFR REQUIRED)
message(STATUS "Found MPFR: ${MPFR_FOUND}")
target_link_libraries(kaleidoscope "${MPFR_LIBRARIES}")