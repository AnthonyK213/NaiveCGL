include(FetchContent)

FetchContent_Declare(
  bvh
  GIT_REPOSITORY https://github.com/madmann91/bvh.git
  GIT_TAG origin/master
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/bvh
  )

# FetchContent_MakeAvailable(bvh)
FetchContent_GetProperties(bvh)
if(NOT bvh_POPULATED)
  FetchContent_Populate(bvh)
  add_subdirectory(
    ${bvh_SOURCE_DIR}
    ${bvh_BINARY_DIR}
    EXCLUDE_FROM_ALL
    )
endif()
