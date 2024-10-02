//
// Created by Josh on 22/09/2024.
//

#pragma once

#include "jve_pipeline.h"
#include "jve_window.h"
#include "jve_swap_chain.h"
#include "jve_device.h"

#include <memory>
#include <vector>

namespace jve {

    class App {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        App();
        ~App();

        App(const App&) = delete;
        App& operator=(const App&) = delete;

    void Run();

    private:

        void CreatePipelineLayout();
        void CreatePipeline();
        void CreateCommandBuffers();
        void DrawFrame();

        JveWindow Window{WIDTH, HEIGHT, "JVE GAME"};
        JveDevice Device{Window};
        JveSwapChain SwapChain{Device, Window.GetExtent()};
        std::unique_ptr<JvePipeline> Pipeline;
        VkPipelineLayout PipelineLayout;
        std::vector<VkCommandBuffer> CommandBuffers;
    };
}