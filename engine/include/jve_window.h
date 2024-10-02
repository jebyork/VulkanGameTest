//
// Created by Josh on 22/09/2024.
//

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace jve {

class JveWindow {

public:
    JveWindow(int width, int height, std::string title);
    ~JveWindow();

    JveWindow(const JveWindow&) = delete;
    JveWindow& operator=(const JveWindow&) = delete;

    bool ShouldClose() const { return glfwWindowShouldClose(Window); }
    VkExtent2D GetExtent() { return {static_cast<uint32_t>(Width), static_cast<uint32_t>(Height)}; }

    void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

private:

    void InitWindow();

    const int Width;
    const int Height;

    std::string WindowTitle;
    GLFWwindow* Window;
};
}