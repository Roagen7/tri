add_library(triutil STATIC)
target_include_directories(triutil PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/triutil)
target_sources(triutil PUBLIC ${SOURCE_DIR}/triutil/files.cpp ${SOURCE_DIR}/triutil/window_init.cpp)
target_link_libraries(triutil PRIVATE glfw glad)
