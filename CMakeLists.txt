cmake_minimum_required(VERSION 3.29)
project(VulkanGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(VulkanGame game/main.cpp)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_subdirectory(engine)
add_subdirectory(game)