add_library(tricore STATIC)
target_include_directories(tricore PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/tricore)
file(GLOB_RECURSE TRICORE_SOURCES
    ${SOURCE_DIR}/tricore/*.cpp
)

target_sources(tricore PUBLIC ${TRICORE_SOURCES})
target_link_libraries(tricore PUBLIC glad triutil fmt glm glfw stb Boost::filesystem)
