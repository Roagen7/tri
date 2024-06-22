add_library(triutil STATIC)
target_include_directories(triutil PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/triutil)

file(GLOB_RECURSE TRIUTIL_SOURCES
    ${SOURCE_DIR}/triutil/*.cpp
)

target_sources(triutil PUBLIC ${TRIUTIL_SOURCES})
target_link_libraries(triutil PRIVATE glfw glad)
