//
// Created by Josh on 25/09/2024.
//
#pragma once
#include <string>
#include <vector>

#include <jve_device.h>

namespace jve {
    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class JvePipeline {
    public:
        JvePipeline(JveDevice& device,
            const std::string& vertFilePath,
            const std::string& fragFilePath,
            const PipelineConfigInfo& configInfo);

        ~JvePipeline();

        JvePipeline(const JvePipeline&) = delete;
        void operator = (const JvePipeline&) = delete;

        void Bind(VkCommandBuffer commandBuffer);
        static PipelineConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);


    private:
        static std::vector<char> readFile(const std::string& filePath);
        void CreateGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo);

        void CreateShaderModule(const std::vector<char>& code, VkShaderModule* module);
        JveDevice& Device;
        VkPipeline GraphicsPipeline;
        VkShaderModule VertShaderModule;
        VkShaderModule FragShaderModule;

    };
}

