cmake_minimum_required(VERSION 3.29)

project(JebVulkanEngine CXX)

add_library(${PROJECT_NAME} src/jve_window.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/engine/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm::glm)