include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
if (MSVC)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES
    *.cpp
)

add_executable(engine_test ${TEST_SOURCES})

target_link_libraries(
  engine_test
  tricore
  GTest::gtest_main
  gmock_main
  glfw
  glm
  triutil
)

target_include_directories(engine_test PUBLIC ${SOURCE_DIR} ${TEST_DIR})

include(GoogleTest)
gtest_discover_tests(engine_test)
