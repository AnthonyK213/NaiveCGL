include(FetchContent)

Fetchcontent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG v1.13.0
  SOURCE_DIR ${CMAKE_BINARY_DIR}/deps/googletest
  )

Fetchcontent_Makeavailable(googletest)

if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)

  # Prevent GoogleTest from overriding our compiler/linker options
  # when building with Visual Studio
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  # Prevent GoogleTest from using PThreads
  set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

  # adds the targers: gtest, gtest_main, gmock, gmock_main
  add_subdirectory(
    ${googletest_SOURCE_DIR}
    ${googletest_BINARY_DIR}
    )

  # Silence std::tr1 warning on MSVC
  if(MSVC)
    foreach(_tgt gtest gtest_main gmock gmock_main)
      target_compile_definitions(${_tgt}
        PRIVATE
        "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
        )
    endforeach()
  endif()
endif()

add_executable(
  ${PROJECT_NAME}Test
  test.cpp
  )

target_include_directories(
  ${PROJECT_NAME}Test
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include/
  ${eigen3_SOURCE_DIR}
  )

target_link_libraries(
  ${PROJECT_NAME}Test
  PRIVATE
  gtest
  ${PROJECT_NAME}
  )

include(GoogleTest)

if(MSVC)
  add_custom_command(
    TARGET ${PROJECT_NAME}Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "$<TARGET_PROPERTY:NaiveCGL,BINARY_DIR>/$<CONFIG>"
      "$<TARGET_PROPERTY:NaiveCGLTest,BINARY_DIR>/$<CONFIG>"
    )
endif()

gtest_discover_tests(${PROJECT_NAME}Test)
