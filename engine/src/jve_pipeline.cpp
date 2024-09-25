//
// Created by Josh on 25/09/2024.
//

#include "jve_pipeline.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace jve {

    JvePipeline::JvePipeline(JveDevice& device,
                             const std::string& vertFilePath,
                             const std::string& fragFilePath,
                             const PipelineConfigInfo& configInfo) : Device(device) {
        std::cout << "Initializing JvePipeline with shaders: " << vertFilePath << ", " << fragFilePath << std::endl;
        CreateGraphicsPipeline(vertFilePath, fragFilePath, configInfo);
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

    void JvePipeline::CreateGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath, const PipelineConfigInfo& configInfo) {
        try {
            auto vertCode = readFile(vertFilePath);
            auto fragCode = readFile(fragFilePath);

            std::cout << "Vertex Shader Code Size: " << vertCode.size() << " bytes" << std::endl;
            std::cout << "Fragment Shader Code Size: " << fragCode.size() << " bytes" << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error during shader compilation: " << e.what() << std::endl;
        }
    }

    void JvePipeline::CreateShaderModule(const std::vector<char> &code, VkShaderModule *module) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        if(vkCreateShaderModule(Device.device(), &createInfo, nullptr, module) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create shader module");
        }

    }

    PipelineConfigInfo JvePipeline::DefaultPipelineConfigInfo(uint32_t width, uint32_t height) {
        PipelineConfigInfo configInfo{};

        configInfo.inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        configInfo.inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        configInfo.inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;
        return configInfo;
    }
}