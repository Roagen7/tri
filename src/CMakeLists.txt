add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})

add_subdirectory(${SOURCE_DIR}/tri)
add_subdirectory(${SOURCE_DIR}/util)
target_link_libraries(${PROJECT_NAME} PRIVATE tri util glfw linmath glad glm)
