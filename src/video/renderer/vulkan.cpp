/**
 * @brief ビデオレンダラー(Vulkan)
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt; @n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include "version.hpp"
#include "vulkan.hpp"

namespace Fullerene::Video::Detail {

struct Vulkan::Impl {
    vk::UniqueInstance Instance;
    vk::UniqueDevice   Device;
    GLFWwindow*        Window;
    Impl () {
        const auto appVersion = VK_MAKE_VERSION(0, 0, 0);
        const auto appName    = "Fullerene";
        const auto appWidth   = 1280;
        const auto appHeight  =  720;

        if (!glfwInit()) throw std::runtime_error("GLFW not initialized");
        CreateInstance(appName, appVersion);
        CreateDevice();
        CreateWindow(appName, appWidth, appHeight);

        while (glfwWindowShouldClose(Window) == GLFW_FALSE) glfwPollEvents();
    }
    ~Impl() {
        glfwTerminate();
    }
    void CreateInstance(const char* name, std::uint32_t version) {
        if (!glfwVulkanSupported()) throw std::runtime_error("Vulkan not supported");
        std::uint32_t extCount   = 0;
        const char**  extNames   = glfwGetRequiredInstanceExtensions(&extCount);
        std::uint32_t lyrCount   = 0;
        const char*   lyrNames[] = { "VK_LAYER_LUNARG_standard_validation" }; 
        vk::ApplicationInfo    appInfo(name, version, SYSTEM_NAME, VK_MAKE_VERSION(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH), VK_API_VERSION_1_2);
        vk::InstanceCreateInfo insInfo({}, &appInfo, lyrCount, lyrNames, extCount, extNames);
        Instance = vk::createInstanceUnique(insInfo);
        return;
    }
    void CreateDevice(void) {
        const auto sizeMax = std::numeric_limits<std::size_t>::max();
        for (auto& device : Instance->enumeratePhysicalDevices()) {
            auto queueIndexPresent  = sizeMax;
            auto queueIndexGraphics = sizeMax;
            auto queueIndexCompute  = sizeMax;
            auto queueIndexTransfer = sizeMax;
            auto properties         = device.getQueueFamilyProperties();
            for (std::size_t i = 0, size = properties.size(); i < size; ++i) {
                auto enablePresent  = glfwGetPhysicalDevicePresentationSupport(*Instance, device, i) != GLFW_FALSE;
                auto enableGraphics = properties[i].queueFlags & vk::QueueFlagBits::eGraphics;
                auto enableCompute  = properties[i].queueFlags & vk::QueueFlagBits::eCompute;
                auto enableTransfer = properties[i].queueFlags & vk::QueueFlagBits::eTransfer;
                if (enablePresent  &&  queueIndexPresent  == sizeMax                                        ) queueIndexPresent  = i;
                if (enableGraphics && (queueIndexGraphics == sizeMax || (                   !enableCompute))) queueIndexGraphics = i;
                if (enableCompute  && (queueIndexCompute  == sizeMax || (!enableGraphics                  ))) queueIndexCompute  = i;
                if (enableTransfer && (queueIndexTransfer == sizeMax || (!enableGraphics && !enableCompute))) queueIndexTransfer = i;
            }
            if (queueIndexPresent != sizeMax) {
                std::vector<std::size_t> queueCount(properties.size());
                if(queueIndexPresent  != sizeMax) ++queueCount[queueIndexPresent ];
                if(queueIndexGraphics != sizeMax) ++queueCount[queueIndexGraphics];
                if(queueIndexCompute  != sizeMax) ++queueCount[queueIndexCompute ];
                if(queueIndexTransfer != sizeMax) ++queueCount[queueIndexTransfer];
                float queuePriority = 1.0f;
                vk::DeviceQueueCreateFlags flags;
                std::vector<vk::DeviceQueueCreateInfo> queueInfos;
                for (std::size_t i = 0, size = queueCount.size(); i < size; ++i) {
                    auto count = std::min<std::size_t>(queueCount[i], properties[i].queueCount);
                    if(count) queueInfos.emplace_back(flags, i, count, &queuePriority);
                }
                vk::DeviceCreateInfo info({}, queueInfos.size(), queueInfos.data());
                Device = device.createDeviceUnique(info);
                return;
            }
        }
        throw std::runtime_error("Device not created");
    }
    void CreateWindow(const char* name, std::size_t width, std::size_t height) {
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        Window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        if (!Window) throw std::runtime_error("Window not created");
        return;
    }
};

Vulkan::Vulkan() {
    if (wpImpl_.expired()) {
        spImpl_ = std::make_shared<Impl>();
        wpImpl_ = spImpl_;
    } else {
        spImpl_ = wpImpl_.lock();
    }
}

std::weak_ptr<Vulkan::Impl> Vulkan::wpImpl_;

} // Fullerene::Video::Detail
