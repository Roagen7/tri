add_library(tricore STATIC)
target_include_directories(tricore PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/tricore)
target_sources(tricore PUBLIC 
${SOURCE_DIR}/tricore/program/Program.cpp
${SOURCE_DIR}/tricore/program/ShaderLib.cpp 
${SOURCE_DIR}/tricore/model/Mesh.cpp 
${SOURCE_DIR}/tricore/model/HeightmapModel.cpp 
${SOURCE_DIR}/tricore/Camera.cpp 
${SOURCE_DIR}/tricore/model/Model.cpp 
${SOURCE_DIR}/tricore/Renderer.cpp
${SOURCE_DIR}/tricore/texture/Texture.cpp
${SOURCE_DIR}/tricore/texture/Cubemap.cpp
${SOURCE_DIR}/tricore/program/shaderError.cpp
${SOURCE_DIR}/tricore/frame/Frame.cpp
${SOURCE_DIR}/tricore/frame/DepthFrame.cpp
${SOURCE_DIR}/tricore/frame/ColorFrame.cpp
)
target_link_libraries(tricore PUBLIC glad triutil fmt glm glfw stb Boost::filesystem)
