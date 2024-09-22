set(GAME_SOURCES main.cpp src/app.cpp)

include_directories(${CMAKE_SOURCE_DIR}/game/include)

add_executable(VulkanGame ${GAME_SOURCES})

target_include_directories(VulkanGame PRIVATE ${CMAKE_SOURCE_DIR}/engine/include)
target_link_libraries(VulkanGame engine_lib)