//
// Created by Josh on 22/09/2024.
//
#include "jve_window.h"

namespace jve {
    JveWindow::JveWindow(int width, int height, std::string title) : Width(width), Height(height), WindowTitle(std::move(title)) {
        InitWindow();
    }

    JveWindow::~JveWindow() {
        glfwDestroyWindow(Window);
        glfwTerminate();
    }

    void JveWindow::InitWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        Window = glfwCreateWindow(Width, Height, WindowTitle.c_str(), nullptr, nullptr);
    }
}