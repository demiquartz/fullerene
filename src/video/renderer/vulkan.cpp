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
    vk::UniqueInstance                   Instance;
    vk::UniqueDevice                     LogicalDevice;
    vk::PhysicalDevice                   PhysicalDevice;
    vk::Queue                            QueuePresent;
    vk::Queue                            QueueGraphics;
    vk::Queue                            QueueCompute;
    vk::Queue                            QueueTransfer;
    vk::UniqueCommandPool                CommandPoolPresent;
    vk::UniqueCommandPool                CommandPoolGraphics;
    vk::UniqueCommandPool                CommandPoolCompute;
    vk::UniqueCommandPool                CommandPoolTransfer;
    GLFWwindow*                          Window;
    vk::UniqueSurfaceKHR                 Surface;
    vk::UniqueSwapchainKHR               Swapchain;
    vk::UniqueImage                      DepthStencil;
    vk::UniqueDeviceMemory               DepthStencilMemory;
    std::vector<vk::UniqueImageView>     ColorImageViews;
    vk::UniqueImageView                  DepthStencilImageView;
    vk::UniqueRenderPass                 RenderPass;
    std::vector<vk::UniqueFramebuffer>   Framebuffers;
    std::vector<vk::UniqueCommandBuffer> CommandBuffersPresent;
    std::vector<vk::UniqueCommandBuffer> CommandBuffersGraphics;
    std::vector<vk::UniqueCommandBuffer> CommandBuffersCompute;
    std::vector<vk::UniqueCommandBuffer> CommandBuffersTransfer;
    vk::UniqueSemaphore                  PresentCompletedSemaphore;
    vk::UniqueSemaphore                  RenderCompletedSemaphore;
    std::vector<vk::UniqueFence>         PresentFences;
    std::uint32_t                        FamilyIndexPresent;
    std::uint32_t                        FamilyIndexGraphics;
    std::uint32_t                        FamilyIndexCompute;
    std::uint32_t                        FamilyIndexTransfer;
    std::uint32_t                        QueueIndexPresent;
    std::uint32_t                        QueueIndexGraphics;
    std::uint32_t                        QueueIndexCompute;
    std::uint32_t                        QueueIndexTransfer;
    Impl () {
        const auto appVersion = VK_MAKE_VERSION(0, 0, 0);
        const auto appName    = "Fullerene";
        const auto appWidth   = 1280;
        const auto appHeight  =  720;
        if (!glfwInit()) throw std::runtime_error("GLFW not initialized");
        CreateInstance(appName, appVersion);
        CreateDevice();
        CreateQueue();
        CreateCommandPool();
        CreateWindow(appName, appWidth, appHeight);
        CreateSurface();
        CreateSwapchain();
        CreateDepthStencil();
        CreateImageViews();
        CreateRenderPass();
        CreateFrameBuffers();
        CreateCommandBuffers();
        CreateSyncPrimitive();
        while (glfwWindowShouldClose(Window) == GLFW_FALSE) {
            Clear(1.0f, 0.5f, 0.0f, 1.0f);
            glfwPollEvents();
        }
    }
    ~Impl() {
        glfwTerminate();
    }
    void CreateInstance(const char* name, std::uint32_t version) {
        if (!glfwVulkanSupported()) throw std::runtime_error("Vulkan not supported");
        auto requiredCount = 0u;
        auto requiredNames = glfwGetRequiredInstanceExtensions(&requiredCount);
        auto systemVersion = VK_MAKE_VERSION(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
        std::vector<const char*> lyrNames({ "VK_LAYER_KHRONOS_validation" });
        std::vector<const char*> extNames(requiredNames, requiredNames + requiredCount);
        vk::ApplicationInfo    appInfo(name, version, SYSTEM_NAME, systemVersion, VK_API_VERSION_1_2);
        vk::InstanceCreateInfo insInfo(vk::InstanceCreateFlags(), &appInfo, lyrNames, extNames);
        Instance = vk::createInstanceUnique(insInfo);
        return;
    }
    void CreateDevice(void) {
        const auto invalid = std::numeric_limits<std::uint32_t>::max();
        for (auto& device : Instance->enumeratePhysicalDevices()) {
            FamilyIndexPresent    = invalid;
            FamilyIndexGraphics   = invalid;
            FamilyIndexCompute    = invalid;
            FamilyIndexTransfer   = invalid;
            auto familyProperties = device.getQueueFamilyProperties();
            for (std::uint32_t i = 0, size = familyProperties.size(); i < size; ++i) {
                auto enablePresent  = glfwGetPhysicalDevicePresentationSupport(*Instance, device, i) != GLFW_FALSE;
                auto enableGraphics = familyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics;
                auto enableCompute  = familyProperties[i].queueFlags & vk::QueueFlagBits::eCompute;
                auto enableTransfer = familyProperties[i].queueFlags & vk::QueueFlagBits::eTransfer;
                if (enablePresent  &&  FamilyIndexPresent  == invalid                                        ) FamilyIndexPresent  = i;
                if (enableGraphics && (FamilyIndexGraphics == invalid || (                   !enableCompute))) FamilyIndexGraphics = i;
                if (enableCompute  && (FamilyIndexCompute  == invalid || (!enableGraphics                  ))) FamilyIndexCompute  = i;
                if (enableTransfer && (FamilyIndexTransfer == invalid || (!enableGraphics && !enableCompute))) FamilyIndexTransfer = i;
            }
            if (FamilyIndexPresent  == invalid) continue;
            if (FamilyIndexGraphics == invalid) continue;
            if (FamilyIndexCompute  == invalid) continue;
            if (FamilyIndexTransfer == invalid) continue;
            std::vector<std::size_t> queueCount(familyProperties.size());
            QueueIndexPresent  = queueCount[FamilyIndexPresent ]++;
            QueueIndexGraphics = queueCount[FamilyIndexGraphics]++;
            QueueIndexCompute  = queueCount[FamilyIndexCompute ]++;
            QueueIndexTransfer = queueCount[FamilyIndexTransfer]++;
            std::vector<vk::DeviceQueueCreateInfo> queueInfos;
            for (std::size_t i = 0, size = queueCount.size(); i < size; ++i) {
                if (queueCount[i] > familyProperties[i].queueCount) break;
                std::vector<float> queuePriorities(queueCount[i], 1.0f);
                queueInfos.emplace_back(vk::DeviceQueueCreateFlags(), i, queuePriorities);
            }
            if (queueInfos.size() != queueCount.size()) continue;
            auto lyrProperties = device.enumerateDeviceLayerProperties    ();
            auto extProperties = device.enumerateDeviceExtensionProperties();
            std::vector<const char*> lyrNames; for (auto& lyr : lyrProperties) lyrNames.push_back(lyr.layerName    );
            std::vector<const char*> extNames; for (auto& ext : extProperties) extNames.push_back(ext.extensionName);
            vk::DeviceCreateInfo info(vk::DeviceCreateFlags(), queueInfos, lyrNames, extNames);
            LogicalDevice  = device.createDeviceUnique(info);
            PhysicalDevice = device;
            return;
        }
        throw std::runtime_error("Device not created");
    }
    void CreateQueue(void) {
        QueuePresent  = LogicalDevice->getQueue(FamilyIndexPresent,  QueueIndexPresent );
        QueueGraphics = LogicalDevice->getQueue(FamilyIndexGraphics, QueueIndexGraphics);
        QueueCompute  = LogicalDevice->getQueue(FamilyIndexCompute,  QueueIndexCompute );
        QueueTransfer = LogicalDevice->getQueue(FamilyIndexTransfer, QueueIndexTransfer);
        return;
    }
    void CreateCommandPool(void) {
        vk::CommandPoolCreateInfo info(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);
        info.queueFamilyIndex = FamilyIndexPresent;
        CommandPoolPresent    = LogicalDevice->createCommandPoolUnique(info);
        info.queueFamilyIndex = FamilyIndexGraphics;
        CommandPoolGraphics   = LogicalDevice->createCommandPoolUnique(info);
        info.queueFamilyIndex = FamilyIndexCompute;
        CommandPoolCompute    = LogicalDevice->createCommandPoolUnique(info);
        info.queueFamilyIndex = FamilyIndexTransfer;
        CommandPoolTransfer   = LogicalDevice->createCommandPoolUnique(info);
        return;
    }
    void CreateWindow(const char* name, std::size_t width, std::size_t height) {
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        Window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        if (!Window) throw std::runtime_error("Window not created");
        return;
    }
    void CreateSurface(void) {
        VkSurfaceKHR surface;
        if (glfwCreateWindowSurface(*Instance, Window, nullptr, &surface) != VK_SUCCESS) throw std::runtime_error("Surface not created");
        Surface = vk::UniqueSurfaceKHR(surface, vk::ObjectDestroy<vk::Instance, vk::DispatchLoaderStatic>(*Instance));
        return;
    }
    void CreateSwapchain(void) {
        auto fmt = PhysicalDevice.getSurfaceFormatsKHR(*Surface)[0];
        auto cap = PhysicalDevice.getSurfaceCapabilitiesKHR(*Surface);
        vk::SwapchainCreateInfoKHR info; // TODO: 後で再調整
        info.surface          = *Surface;
        info.minImageCount    = std::clamp(3u, cap.minImageCount, cap.maxImageCount);
        info.imageFormat      = fmt.format;
        info.imageColorSpace  = fmt.colorSpace;
        info.imageExtent      = cap.currentExtent;
        info.imageArrayLayers = 1;
        info.imageUsage       = cap.supportedUsageFlags;
        info.presentMode      = info.minImageCount == 3 ? vk::PresentModeKHR::eMailbox : vk::PresentModeKHR::eFifo;
        info.clipped          = VK_TRUE;
        Swapchain             = LogicalDevice->createSwapchainKHRUnique(info);
        return;
    }
    void CreateDepthStencil(void) {
        auto cap = PhysicalDevice.getSurfaceCapabilitiesKHR(*Surface);
        vk::ImageCreateInfo info; // TODO: 後で再調整
        info.imageType       = vk::ImageType::e2D;
        info.format          = vk::Format::eD24UnormS8Uint;
        info.extent          = vk::Extent3D(cap.currentExtent, 1);
        info.mipLevels       = 1;
        info.arrayLayers     = 1;
        info.usage           = vk::ImageUsageFlagBits::eDepthStencilAttachment;
        DepthStencil         = LogicalDevice->createImageUnique(info);
        auto requirements    = LogicalDevice->getImageMemoryRequirements(*DepthStencil);
        auto properties      = PhysicalDevice.getMemoryProperties();
        auto memoryTypeIndex = 0u;
        for (std::uint32_t i = 0, size = properties.memoryTypeCount; i < size; ++i) {
            if (requirements.memoryTypeBits & 1) {
                auto& types = properties.memoryTypes[i];
                if (types.propertyFlags & vk::MemoryPropertyFlagBits::eDeviceLocal) {
                    memoryTypeIndex = i;
                    break;
                }
            }
            requirements.memoryTypeBits >>= 1;
        }
        vk::MemoryAllocateInfo allocInfo(requirements.size, memoryTypeIndex);
        DepthStencilMemory = LogicalDevice->allocateMemoryUnique(allocInfo);
        LogicalDevice->bindImageMemory(*DepthStencil, *DepthStencilMemory, 0);
        return;
    }
    void CreateImageViews(void) {
        vk::ComponentMapping components(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA);
        auto fmt    = PhysicalDevice.getSurfaceFormatsKHR(*Surface)[0];
        auto images = LogicalDevice->getSwapchainImagesKHR(*Swapchain);
        for (auto& image : images) {
            vk::ImageSubresourceRange subresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1);
            vk::ImageViewCreateInfo info(vk::ImageViewCreateFlags(), image, vk::ImageViewType::e2D, fmt.format, components, subresourceRange);
            ColorImageViews.emplace_back(LogicalDevice->createImageViewUnique(info));
        }
        vk::ImageSubresourceRange subresourceRange(vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil, 0, 1, 0, 1);
        vk::ImageViewCreateInfo info(vk::ImageViewCreateFlags(), *DepthStencil, vk::ImageViewType::e2D, vk::Format::eD24UnormS8Uint, components, subresourceRange);
        DepthStencilImageView = LogicalDevice->createImageViewUnique(info);
        return;
    }
    void CreateRenderPass(void) {
        auto fmt = PhysicalDevice.getSurfaceFormatsKHR(*Surface)[0];
        std::array<vk::AttachmentDescription, 2> attachments;
        std::array<vk::SubpassDescription,    1> subpasses;
        auto& colorAttachment       = attachments[0];
        auto& depthAttachment       = attachments[1];
        colorAttachment.format      = fmt.format;
        colorAttachment.loadOp      = vk::AttachmentLoadOp::eClear;
        colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;
        depthAttachment.format      = vk::Format::eD24UnormS8Uint;
        depthAttachment.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
        std::array<vk::AttachmentReference, 1> colorReference;
        colorReference[0] = { 0, vk::ImageLayout::ePresentSrcKHR                 };
        std::array<vk::AttachmentReference, 1> depthReference;
        depthReference[0] = { 1, vk::ImageLayout::eDepthStencilAttachmentOptimal };
        subpasses[0].setPipelineBindPoint(vk::PipelineBindPoint::eGraphics);
        subpasses[0].setColorAttachments       (colorReference       );
        subpasses[0].setPDepthStencilAttachment(depthReference.data());
        vk::RenderPassCreateInfo info(vk::RenderPassCreateFlags(), attachments, subpasses);
        RenderPass = LogicalDevice->createRenderPassUnique(info);
        return;
    }
    void CreateFrameBuffers(void) {
        auto cap = PhysicalDevice.getSurfaceCapabilitiesKHR(*Surface);
        vk::FramebufferCreateInfo info;
        info.renderPass = *RenderPass;
        info.width      = cap.currentExtent.width;
        info.height     = cap.currentExtent.height;
        info.layers     = 1;
        for (auto& view : ColorImageViews) {
            std::array<vk::ImageView, 2> attachments{ *view, *DepthStencilImageView };
            info.setAttachments(attachments);
            Framebuffers.push_back(LogicalDevice->createFramebufferUnique(info));
        }
        return;
    }
    void CreateCommandBuffers(void) {
        vk::CommandBufferAllocateInfo info;
        info.commandPool        = *CommandPoolPresent;
        info.level              = vk::CommandBufferLevel::ePrimary;
        info.commandBufferCount = ColorImageViews.size();
        CommandBuffersPresent   = LogicalDevice->allocateCommandBuffersUnique(info);
        info.commandPool        = *CommandPoolGraphics;
        info.level              = vk::CommandBufferLevel::ePrimary;
        info.commandBufferCount = 1;
        CommandBuffersGraphics  = LogicalDevice->allocateCommandBuffersUnique(info);
        info.commandPool        = *CommandPoolCompute;
        info.level              = vk::CommandBufferLevel::ePrimary;
        info.commandBufferCount = 1;
        CommandBuffersCompute   = LogicalDevice->allocateCommandBuffersUnique(info);
        info.commandPool        = *CommandPoolTransfer;
        info.level              = vk::CommandBufferLevel::ePrimary;
        info.commandBufferCount = 1;
        CommandBuffersTransfer  = LogicalDevice->allocateCommandBuffersUnique(info);
        return;
    }
    void CreateSyncPrimitive(void) {
        for (std::size_t i = 0, size = ColorImageViews.size(); i < size; ++i) {
            vk::FenceCreateInfo info(vk::FenceCreateFlagBits::eSignaled);
            PresentFences.push_back(LogicalDevice->createFenceUnique(info));
        }
        PresentCompletedSemaphore = LogicalDevice->createSemaphoreUnique({});
        RenderCompletedSemaphore  = LogicalDevice->createSemaphoreUnique({});
    }
    void Clear(float r, float g, float b, float a) {
        auto cap = PhysicalDevice.getSurfaceCapabilitiesKHR(*Surface);
        std::uint32_t imageIndex;
        LogicalDevice->acquireNextImageKHR(*Swapchain, std::numeric_limits<std::uint64_t>::max(), *PresentCompletedSemaphore, nullptr, &imageIndex);
//        LogicalDevice->waitForFences(1, &(*PresentFences[imageIndex]), VK_TRUE, std::numeric_limits<std::uint64_t>::max());
        std::array<vk::ClearValue, 2> clearValues;
        clearValues[0].color.float32[0]     =   r;
        clearValues[0].color.float32[1]     =   g;
        clearValues[0].color.float32[2]     =   b;
        clearValues[0].color.float32[3]     =   a;
        clearValues[1].depthStencil.depth   = 1.0;
        clearValues[1].depthStencil.stencil =   0;
        vk::Rect2D renderArea({ 0, 0 }, cap.currentExtent);
        vk::CommandBufferBeginInfo info;
        CommandBuffersPresent[imageIndex]->begin(info);
        vk::RenderPassBeginInfo rpInfo(*RenderPass, *Framebuffers[imageIndex], renderArea, clearValues);
        CommandBuffersPresent[imageIndex]->beginRenderPass(rpInfo, vk::SubpassContents::eInline);
        std::vector<vk::CommandBuffer> commandBuffers;
        for (auto& commandBuffer : CommandBuffersPresent) {
            commandBuffers.push_back(*commandBuffer);
        }
        vk::PipelineStageFlags waitStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        std::array<vk::SubmitInfo, 1> submitInfos;
        submitInfos[0].setCommandBuffers(commandBuffers);
        submitInfos[0].pWaitDstStageMask    = &waitStageMask;
        submitInfos[0].waitSemaphoreCount   = 1;
        submitInfos[0].pWaitSemaphores      = &PresentCompletedSemaphore.get();
        submitInfos[0].signalSemaphoreCount = 1;
        submitInfos[0].pSignalSemaphores    = &RenderCompletedSemaphore.get();
//        LogicalDevice->resetFences(1, &(*PresentFences[imageIndex]));
        QueuePresent.submit(submitInfos);
        vk::PresentInfoKHR presentInfo;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores    = &PresentCompletedSemaphore.get();
        presentInfo.swapchainCount     = 1;
        presentInfo.pSwapchains        = &Swapchain.get();
        presentInfo.pImageIndices      = &imageIndex;
        QueuePresent.presentKHR(presentInfo);
        CommandBuffersPresent[imageIndex]->endRenderPass();
        CommandBuffersPresent[imageIndex]->end();
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
