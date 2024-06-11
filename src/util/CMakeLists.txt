add_library(util STATIC)
target_include_directories(util PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/util)
target_sources(util PUBLIC ${SOURCE_DIR}/util/files.cpp)
