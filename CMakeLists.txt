cmake_minimum_required(VERSION 3.20)

project(
  NaiveCGL
  VERSION 0.0.1
  LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION})

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory 
  (or any directory with a CMakeLists.txt file). Please make a 
  build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

option(NAIVECGL_BUILD_STATIC "Build static library" OFF)

include(cmake/FetchDeps.cmake)

message("eigen3_SOURCE_DIR: ${eigen3_SOURCE_DIR}")
message("eigen3_BINARY_DIR: ${eigen3_BINARY_DIR}")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  ${eigen3_SOURCE_DIR}
  )

add_subdirectory(src)

if(ENABLE_UNIT_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
