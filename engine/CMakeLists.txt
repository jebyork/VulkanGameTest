set(ENGINE_SOURCES src/jve_window.cpp)

include_directories(include)

add_library(${PROJECT_NAME} src/jve_window.cpp)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_library(engine_lib STATIC ${ENGINE_SOURCES})
target_link_libraries(engine_lib Vulkan::Vulkan glfw glm::glm)