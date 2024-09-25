//
// Created by Josh on 25/09/2024.
//

#include "jve_pipeline.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace jve {

    JvePipeline::JvePipeline(const std::string &verFilePath, const std::string &fragFilePath) {
        std::cout << "Initializing JvePipeline with shaders: " << verFilePath << ", " << fragFilePath << std::endl;
        CreateGraphicsPipeline(verFilePath, fragFilePath);
    }

    std::vector<char> JvePipeline::readFile(const std::string &filePath) {
        std::ifstream file(filePath, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        return buffer;
    }

    void JvePipeline::CreateGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath) {
        try {
            auto vertCode = readFile(vertFilePath);
            auto fragCode = readFile(fragFilePath);

            std::cout << "Vertex Shader Code Size: " << vertCode.size() << " bytes" << std::endl;
            std::cout << "Fragment Shader Code Size: " << fragCode.size() << " bytes" << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error during shader compilation: " << e.what() << std::endl;
        }
    }
}