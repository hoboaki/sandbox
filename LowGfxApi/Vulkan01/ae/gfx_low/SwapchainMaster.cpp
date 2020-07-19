// 文字コード：UTF-8
#include <ae/gfx_low/SwapchainMaster.hpp>

// includes
#include <ae/base/ArrayLength.hpp>
#include <ae/base/Display.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/SwapchainCreateInfo.hpp>
#include <ae/gfx_low/SwapchainEntity.hpp>
#include <ae/gfx_low/SwapchainMasterCreateInfo.hpp>
#include <ae/gfx_low/System.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
SwapchainMaster::SwapchainMaster(const SwapchainMasterCreateInfo& createInfo)
: device_(::ae::base::PtrToRef(createInfo.Device()))
, surface_()
, entities_(createInfo.SwapchainCountMax(),
      &device_.System().InternalObjectAllocator()) {
    // surface 作成
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {
        auto& display = base::PtrToRef(createInfo.Display());
        auto const surfaceCreateInfo =
            ::vk::Win32SurfaceCreateInfoKHR()
                .setHinstance(display.ext_().hinstance)
                .setHwnd(display.ext_().hwindow);

        auto result = device_.System().InternalInstance().createWin32SurfaceKHR(
            &surfaceCreateInfo, nullptr, &surface_);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
    }
#elif defined(VK_USE_PLATFORM_METAL_EXT)
    {
        auto const createInfo = vk::MetalSurfaceCreateInfoEXT().setPLayer(
            static_cast<CAMetalLayer*>(caMetalLayer));

        auto result =
            inst.createMetalSurfaceEXT(&createInfo, nullptr, &surface);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
    }
#endif
}

//------------------------------------------------------------------------------
SwapchainMaster::~SwapchainMaster() {
    // 逆順に破棄
    for (int i = entities_.count() - 1; 0 <= i; --i) {
        auto& entity = entities_[i];
        if (entity.swapchainMaster.isValid()) {
            DestroySwapchain(SwapchainHandle::InternalCreate(&entity));
        }
    }
    device_.System().InternalInstance().destroySurfaceKHR(surface_, nullptr);
    surface_ = ::vk::SurfaceKHR();
}

//------------------------------------------------------------------------------
SwapchainHandle SwapchainMaster::CreateSwapchain(
    const SwapchainCreateInfo& createInfo,
    const SwapchainHandle& oldSwapchain) {
    // メモ
    const auto& physicalDevice =
        device_.System().InternalPhysicalDevice(device_.PhysicalDeviceIndex());
    uint32_t width = 500;
    uint32_t height = 500;

    // 古い swapchain をメモ
    SwapchainEntity* entity = nullptr;
    ::vk::SwapchainKHR oldSwapchainInstance;
    if (oldSwapchain.IsValid()) {
        oldSwapchain.InternalEntity().swapchain;
        entity = &oldSwapchain.InternalEntity();
    }

    // Entity を確保
    const uint32_t nextUniqueId = AcquireUniqueId();
    if (entity == nullptr) {
        for (int entityIdx = 0; entityIdx < entities_.count(); ++entityIdx) {
            if (entities_[entityIdx].swapchainMaster.isNull()) {
                entity = &entities_[entityIdx];
                break;
            }
        }
    }
    *entity = SwapchainEntity();
    entity->swapchainMaster.reset(this);
    entity->uniqueId = nextUniqueId;

    // Get the list of VkFormat's that are supported:
    uint32_t formatCount;
    vk::Format format;
    vk::ColorSpaceKHR color_space;
    auto result = physicalDevice.getSurfaceFormatsKHR(
        surface_, &formatCount, static_cast<vk::SurfaceFormatKHR*>(nullptr));
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    std::unique_ptr<vk::SurfaceFormatKHR[]> surfFormats(
        new vk::SurfaceFormatKHR[formatCount]);
    result = physicalDevice.getSurfaceFormatsKHR(
        surface_, &formatCount, surfFormats.get());
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    // If the format list includes just one entry of VK_FORMAT_UNDEFINED,
    // the surface has no preferred format.  Otherwise, at least one
    // supported format will be returned.
    if (formatCount == 1 && surfFormats[0].format == vk::Format::eUndefined) {
        format = vk::Format::eB8G8R8A8Unorm;
    } else {
        assert(formatCount >= 1);
        format = surfFormats[0].format;
    }
    color_space = surfFormats[0].colorSpace;

    // Check the surface capabilities and formats
    ::vk::SurfaceCapabilitiesKHR surfCapabilities;
    result =
        physicalDevice.getSurfaceCapabilitiesKHR(surface_, &surfCapabilities);
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    uint32_t presentModeCount;
    result = physicalDevice.getSurfacePresentModesKHR(
        surface_, &presentModeCount, static_cast<vk::PresentModeKHR*>(nullptr));
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    std::unique_ptr<vk::PresentModeKHR[]> presentModes(
        new vk::PresentModeKHR[presentModeCount]);
    result = physicalDevice.getSurfacePresentModesKHR(
        surface_, &presentModeCount, presentModes.get());
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    vk::Extent2D swapchainExtent;
    // width and height are either both -1, or both not -1.
    if (surfCapabilities.currentExtent.width == (uint32_t)-1) {
        // If the surface size is undefined, the size is set to
        // the size of the images requested.
        swapchainExtent.width = width;
        swapchainExtent.height = height;
    } else {
        // If the surface size is defined, the swap chain size must match
        swapchainExtent = surfCapabilities.currentExtent;
        width = surfCapabilities.currentExtent.width;
        height = surfCapabilities.currentExtent.height;
    }

    // The FIFO present mode is guaranteed by the spec to be supported
    // and to have no tearing.  It's a great default present mode to use.
    vk::PresentModeKHR swapchainPresentMode = vk::PresentModeKHR::eFifo;

    //  There are times when you may wish to use another present mode.  The
    //  following code shows how to select them, and the comments provide some
    //  reasons you may wish to use them.
    //
    // It should be noted that Vulkan 1.0 doesn't provide a method for
    // synchronizing rendering with the presentation engine's display.  There
    // is a method provided for throttling rendering with the display, but
    // there are some presentation engines for which this method will not work.
    // If an application doesn't throttle its rendering, and if it renders much
    // faster than the refresh rate of the display, this can waste power on
    // mobile devices.  That is because power is being spent rendering images
    // that may never be seen.

    // VK_PRESENT_MODE_IMMEDIATE_KHR is for applications that don't care
    // about
    // tearing, or have some way of synchronizing their rendering with the
    // display.
    // VK_PRESENT_MODE_MAILBOX_KHR may be useful for applications that
    // generally render a new presentable image every refresh cycle, but are
    // occasionally early.  In this case, the application wants the new
    // image
    // to be displayed instead of the previously-queued-for-presentation
    // image
    // that has not yet been displayed.
    // VK_PRESENT_MODE_FIFO_RELAXED_KHR is for applications that generally
    // render a new presentable image every refresh cycle, but are
    // occasionally
    // late.  In this case (perhaps because of stuttering/latency concerns),
    // the application wants the late image to be immediately displayed,
    // even
    // though that may mean some tearing.

    ::vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;
    if (presentMode != swapchainPresentMode) {
        for (size_t i = 0; i < presentModeCount; ++i) {
            if (presentModes[i] == presentMode) {
                swapchainPresentMode = presentMode;
                break;
            }
        }
    }

    if (swapchainPresentMode != presentMode) {
        AE_BASE_ASSERT_NOT_REACHED_MSG(
            "Present mode specified is not supported\n");
    }

    // Determine the number of VkImages to use in the swap chain.
    // Application desires to acquire 3 images at a time for triple
    // buffering
    uint32_t desiredNumOfSwapchainImages = uint32_t(createInfo.ImageCount());
    if (desiredNumOfSwapchainImages < surfCapabilities.minImageCount) {
        desiredNumOfSwapchainImages = surfCapabilities.minImageCount;
    }

    // If maxImageCount is 0, we can ask for as many images as we want,
    // otherwise
    // we're limited to maxImageCount
    if ((surfCapabilities.maxImageCount > 0) &&
        (desiredNumOfSwapchainImages > surfCapabilities.maxImageCount)) {
        // Application must settle for fewer images than desired:
        desiredNumOfSwapchainImages = surfCapabilities.maxImageCount;
    }

    vk::SurfaceTransformFlagBitsKHR preTransform;
    if (surfCapabilities.supportedTransforms &
        vk::SurfaceTransformFlagBitsKHR::eIdentity) {
        preTransform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
    } else {
        preTransform = surfCapabilities.currentTransform;
    }

    // Find a supported composite alpha mode - one of these is guaranteed to be
    // set
    vk::CompositeAlphaFlagBitsKHR compositeAlpha =
        vk::CompositeAlphaFlagBitsKHR::eOpaque;
    vk::CompositeAlphaFlagBitsKHR compositeAlphaFlags[4] = {
        vk::CompositeAlphaFlagBitsKHR::eOpaque,
        vk::CompositeAlphaFlagBitsKHR::ePreMultiplied,
        vk::CompositeAlphaFlagBitsKHR::ePostMultiplied,
        vk::CompositeAlphaFlagBitsKHR::eInherit,
    };
    for (uint32_t i = 0; i < AE_BASE_ARRAY_LENGTH(compositeAlphaFlags); i++) {
        if (surfCapabilities.supportedCompositeAlpha & compositeAlphaFlags[i]) {
            compositeAlpha = compositeAlphaFlags[i];
            break;
        }
    }

    auto const swapchain_ci =
        vk::SwapchainCreateInfoKHR()
            .setSurface(surface_)
            .setMinImageCount(desiredNumOfSwapchainImages)
            .setImageFormat(format)
            .setImageColorSpace(color_space)
            .setImageExtent({swapchainExtent.width, swapchainExtent.height})
            .setImageArrayLayers(1)
            .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
            .setImageSharingMode(vk::SharingMode::eExclusive)
            .setQueueFamilyIndexCount(0)
            .setPQueueFamilyIndices(nullptr)
            .setPreTransform(preTransform)
            .setCompositeAlpha(compositeAlpha)
            .setPresentMode(swapchainPresentMode)
            .setClipped(true)
            .setOldSwapchain(oldSwapchain.IsValid()
                                 ? oldSwapchain.InternalEntity().swapchain
                                 : ::vk::SwapchainKHR());

    result = device_.InternalInstance().createSwapchainKHR(
        &swapchain_ci, nullptr, &entity->swapchain);
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    if (oldSwapchain.IsValid()) {
        DestroySwapchainInstance(oldSwapchainInstance);
    }

    return SwapchainHandle::InternalCreate(entity);
}

//------------------------------------------------------------------------------
void SwapchainMaster::DestroySwapchain(const SwapchainHandle& swapchain) {
    AE_BASE_ASSERT(swapchain.IsValid());
    auto& entity = swapchain.InternalEntity();
    AE_BASE_ASSERT(this == entity.swapchainMaster.get());

    // 破棄
    DestroySwapchainInstance(entity.swapchain);
    entity = SwapchainEntity();
}

//------------------------------------------------------------------------------
uint32_t SwapchainMaster::AcquireUniqueId() {
    uint32_t uniqueId = lastAcquireUniqueId_;
    while (true) {
        ++uniqueId;
        if (uniqueId == SwapchainEntity::InvalidUniqueId) {
            continue;
        }
        bool isFound = false;
        for (int i = 0; i < entities_.count(); ++i) {
            if (entities_[i].uniqueId == uniqueId) {
                isFound = true;
                break;
            }
        }
        if (isFound) {
            continue;
        }
        break;
    }
    lastAcquireUniqueId_ = uniqueId;
    return uniqueId;
}

//------------------------------------------------------------------------------
void SwapchainMaster::DestroySwapchainInstance(::vk::SwapchainKHR instance) {
    device_.InternalInstance().destroySwapchainKHR(instance);
}

}  // namespace gfx_low
}  // namespace ae
// EOF