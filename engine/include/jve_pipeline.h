//
// Created by Josh on 25/09/2024.
//
#pragma once
#include <string>
#include <vector>

namespace jve {
    class JvePipeline {
    public:
        JvePipeline(const std::string& verFilePath, const std::string& fragFilePath);

    private:
        static std::vector<char> readFile(const std::string& filePath);
        void CreateGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath);

    };
}


