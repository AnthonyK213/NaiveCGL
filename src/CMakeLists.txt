aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} NAIVECGL_SRC)

if(NAIVECGL_BUILD_STATIC)
  add_library(
    ${PROJECT_NAME}
    STATIC
    ${NAIVECGL_SRC}
    )
else()
  add_library(
    ${PROJECT_NAME}
    SHARED
    ${NAIVECGL_SRC}
    )
endif()

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${bvh_SOURCE_DIR}/src
  ${eigen3_SOURCE_DIR}
  )

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  Eigen3::Eigen
  )

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION include
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  )

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION include
  COMPONENT header_files
  FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.inl"
  )

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION lib/cmake/naivecgl
  )

set(INCLUDE_DIR include)
set(LIBRARIES ${PROJECT_NAME})
set(LIBRARY_DIR lib)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION 0.0.1
  COMPATIBILITY SameMajorVersion
  )

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION lib/cmake/naivecgl
  PATH_VARS INCLUDE_DIR LIBRARIES LIBRARY_DIR
  INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
  )

install(
  FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION lib/cmake/naivecgl
  )

