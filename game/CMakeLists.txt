set(GAME_SOURCES main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/game/include)

add_executable(VulkanGame ${GAME_SOURCES} src/app.cpp main.cpp)

target_link_libraries(VulkanGame engine_lib)