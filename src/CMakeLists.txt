file(
  GLOB
  NAIVECGL_SRC
  *.cpp
  )

add_library(
  ${PROJECT_NAME}
  SHARED
  ${NAIVECGL_SRC}
  )

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include/naivecgl/
  )

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  Eigen3::Eigen
  )
