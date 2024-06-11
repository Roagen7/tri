add_library(tri STATIC)
target_include_directories(tri PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/tri)
target_sources(tri PUBLIC ${SOURCE_DIR}/tri/program/Program.cpp ${SOURCE_DIR}/tri/Mesh.cpp)
target_link_libraries(tri PUBLIC glad util fmt glm)
