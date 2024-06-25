add_library(triextra STATIC)
target_include_directories(triextra PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/triextra)

file(GLOB_RECURSE TRIUTIL_SOURCES
    ${SOURCE_DIR}/triextra/*.cpp
)

target_sources(triextra PUBLIC ${TRIUTIL_SOURCES})
target_link_libraries(triextra PRIVATE glad tricore)
