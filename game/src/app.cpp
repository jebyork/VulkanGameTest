//
// Created by Josh on 22/09/2024.
//

#include "app.h"

namespace jve {
    void App::Run() {
        while(!Window.ShouldClose()) {
            glfwPollEvents();
        }
    }

}