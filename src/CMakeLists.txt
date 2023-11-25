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

target_link_libraries(
  ${PROJECT_NAME}
  )

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include/naivecgl/
  )
