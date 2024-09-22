//
// Created by Josh on 22/09/2024.
//

#pragma once

#include "jve_window.h"

namespace jve {

class App {
    public:
      static constexpr int WIDTH = 800;
      static constexpr int HEIGHT = 600;

    void Run();

    private:
    JveWindow Window{WIDTH, HEIGHT, "JVE GAME"};

};
}