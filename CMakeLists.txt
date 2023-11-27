cmake_minimum_required(VERSION 3.20)

if(WIN32)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory 
  (or any directory with a CMakeLists.txt file). Please make a 
  build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

find_package(Eigen3 REQUIRED)
message(${EIGEN3_INCLUDE_DIRS})

include_directories(
  ${PROJECT_BINARY_DIR}
  ${EIGEN3_INCLUDE_DIRS}
  )

add_subdirectory(src)

if(ENABLE_UNIT_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
