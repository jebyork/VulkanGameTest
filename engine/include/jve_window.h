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
  private:

    void InitWindow();

    const int Width;
    const int Height;

    std::string WindowTitle;
    GLFWwindow* Window;
};
}