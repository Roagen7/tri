add_library(util STATIC)
target_include_directories(util PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/util)
target_sources(util PUBLIC ${SOURCE_DIR}/util/files.cpp ${SOURCE_DIR}/util/window_init.cpp)
target_link_libraries(util PRIVATE glfw glad)
