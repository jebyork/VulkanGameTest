#include <exception>

#include "include/app.h"

#include <cstdlib>
#include <iostream>

int main() {
    jve::App app{};

    try {
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
