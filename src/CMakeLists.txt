add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})

add_subdirectory(${SOURCE_DIR}/tricore)
add_subdirectory(${SOURCE_DIR}/triutil)
target_link_libraries(${PROJECT_NAME} PRIVATE tricore triutil glfw linmath glad glm)
