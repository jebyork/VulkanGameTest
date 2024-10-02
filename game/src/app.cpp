//
// Created by Josh on 22/09/2024.
//

#include "app.h"

#include <array>
#include <stdexcept>

namespace jve {
    App::App() {
        CreatePipelineLayout();
        CreatePipeline();
        CreateCommandBuffers();
    }

    App::~App() {
        vkDestroyPipelineLayout(Device.device(), PipelineLayout, nullptr);
    }

    void App::Run() {
        while(!Window.ShouldClose()) {
            glfwPollEvents();
            DrawFrame();
        }

        vkDeviceWaitIdle(Device.device());
    }

    void App::CreatePipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;
        if(vkCreatePipelineLayout(Device.device(), &pipelineLayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout!");
        }
    }

    void App::CreatePipeline() {
        auto pipelineConfig = JvePipeline::DefaultPipelineConfigInfo(SwapChain.width(), SwapChain.height());
        pipelineConfig.renderPass = SwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = PipelineLayout;
        Pipeline = std::make_unique<JvePipeline>(
            Device,
            "../engine/shaders/simple_shader.vert.spv",
            "../engine/shaders/simple_shader.frag.spv",
            pipelineConfig
            );
    }

    void App::CreateCommandBuffers() {
        CommandBuffers.resize(SwapChain.imageCount());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = Device.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(CommandBuffers.size());

        if (vkAllocateCommandBuffers(Device.device(), &allocInfo, CommandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffers!");
        }

        for(int i = 0; i < CommandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if(vkBeginCommandBuffer(CommandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("Failed to begin command buffer operation!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = SwapChain.getRenderPass();
            renderPassInfo.framebuffer = SwapChain.getFrameBuffer(i);

            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = SwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.1f, 0.1f, 0.1f, 0.1f};
            clearValues[1].depthStencil = {1.0f, 0};
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(CommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            Pipeline->Bind(CommandBuffers[i]);
            vkCmdDraw(CommandBuffers[i], 3, 1, 0, 0);

            vkCmdEndRenderPass(CommandBuffers[i]);
            if (vkEndCommandBuffer(CommandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("Failed to end command buffer operation!");
            }
        }
    }

    void App::DrawFrame() {
        uint32_t imageIndex = 0;
        auto result = SwapChain.acquireNextImage(&imageIndex);

        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("Failed to acquire swap chain image!");
        }

        result = SwapChain.submitCommandBuffers(&CommandBuffers[imageIndex], &imageIndex);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to submit command buffer to swap chain!");
        }
    }
}
