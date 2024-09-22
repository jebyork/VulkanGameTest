cmake_minimum_required(VERSION 3.29)

project(JebGame CXX)

# Ensure that the JebVulkanEngine library is available
set(ENGINE_LIB JebVulkanEngine)

add_executable(${PROJECT_NAME} main.cpp src/app.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/game/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/engine/include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${ENGINE_LIB})