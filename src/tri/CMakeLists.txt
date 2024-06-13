add_library(tri STATIC)
target_include_directories(tri PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/tri)
target_sources(tri PUBLIC 
${SOURCE_DIR}/tri/program/Program.cpp 
${SOURCE_DIR}/tri/model/Mesh.cpp 
${SOURCE_DIR}/tri/Camera.cpp 
${SOURCE_DIR}/tri/model/Model.cpp 
${SOURCE_DIR}/tri/Renderer.cpp
${SOURCE_DIR}/tri/texture/Texture.cpp
)
target_link_libraries(tri PUBLIC glad util fmt glm glfw stb)
