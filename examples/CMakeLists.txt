add_executable(tri_scene1 scene1.cpp)
target_link_libraries(tri_scene1 PUBLIC tricore triutil glm glad glfw)

add_executable(tri_scene2 scene2.cpp)
target_link_libraries(tri_scene2 PUBLIC tricore triutil glm glad glfw)

add_executable(tri_scene3 scene3.cpp)
target_link_libraries(tri_scene3 PUBLIC tricore triutil glm glad glfw)

add_executable(tri_scene4 scene4.cpp)
target_link_libraries(tri_scene4 PUBLIC tricore triutil triextra glm glad glfw)