set(ENGINE_SOURCES src/jve_window.cpp
        src/jve_device.cpp
        src/jve_pipeline.cpp
        src/jve_swap_chain.cpp
        )

include_directories(include)

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_library(engine_lib STATIC ${ENGINE_SOURCES})
target_include_directories(engine_lib PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(engine_lib Vulkan::Vulkan glfw glm::glm)

# Specify the shaders directory within the engine
set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

# Copy shaders to the build directory
add_custom_target(copy_shaders ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/shaders"
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_DIR} "${CMAKE_CURRENT_BINARY_DIR}/shaders"
)

# Ensure shaders are copied before building the engine library
add_dependencies(engine_lib copy_shaders)