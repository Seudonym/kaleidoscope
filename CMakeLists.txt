cmake_minimum_required(VERSION 3.27)
project(kaleidoscope VERSION 0.1.0 LANGUAGES C CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(kaleidoscope main.cpp include/Globals.cpp include/Mandelbrot.cpp)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(MPFR REQUIRED)
message(STATUS "Found MPFR: ${MPFR_FOUND}")
target_link_libraries(kaleidoscope "${MPFR_LIBRARIES}")

# set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics window system REQUIRED)
message(STATUS "Found SFML: ${SFML_FOUND}")
target_link_libraries(kaleidoscope "${SFML_LIBRARIES}")