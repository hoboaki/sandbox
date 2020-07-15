// 文字コード：UTF-8
#include <ae/gfx_low/System.hpp>

#include <ae/base/ArrayLength.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/PhysicalDeviceInfo.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

namespace {

bool fCheckLayers(uint32_t checkCount, char const* const* const checkNames,
    uint32_t layerCount, ::vk::LayerProperties* layers) {
    for (uint32_t i = 0; i < checkCount; i++) {
        bool found = false;
        for (uint32_t j = 0; j < layerCount; j++) {
            if (!::std::strcmp(checkNames[i], layers[j].layerName)) {
                found = true;
                break;
            }
        }
        if (!found) {
            fprintf(stderr, "Cannot find layer: %s\n", checkNames[i]);
            return false;
        }
    }
    return true;
}

}  // namespace

//------------------------------------------------------------------------------
System::System(const SystemCreateInfo& createInfo) {
    // 複数作成防止
    AE_BASE_ASSERT(!IsInstanceCreated);
    IsInstanceCreated = true;

    // ValidationLayer 検索
    char const* const instanceValidationLayers[] = {
        "VK_LAYER_KHRONOS_validation"};
    uint32_t instanceLayerCount = 0;
    vk::Bool32 validation_found = VK_FALSE;
    if (createInfo.DebugLevel() != SystemDebugLevel::NoDebug) {
        auto result = vk::enumerateInstanceLayerProperties(
            &instanceLayerCount, static_cast<vk::LayerProperties*>(nullptr));
        AE_BASE_ASSERT(result == vk::Result::eSuccess);

        if (0 < instanceLayerCount) {
            std::unique_ptr<vk::LayerProperties[]> instance_layers(
                new vk::LayerProperties[instanceLayerCount]);
            result = vk::enumerateInstanceLayerProperties(
                &instanceLayerCount, instance_layers.get());
            AE_BASE_ASSERT(result == vk::Result::eSuccess);

            validation_found =
                fCheckLayers(AE_BASE_ARRAY_LENGTH(instanceValidationLayers),
                    instanceValidationLayers, instanceLayerCount,
                    instance_layers.get());
            if (validation_found) {
                enabledLayerCount_ =
                    AE_BASE_ARRAY_LENGTH(instanceValidationLayers);
                enabledLayers_[0] = "VK_LAYER_KHRONOS_validation";
            }
        }

        if (!validation_found) {
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "vkEnumerateInstanceLayerProperties failed to find required "
                "validation layer.\n\n"
                "Please look at the Getting Started guide for additional "
                "information.\n");
        }
    }

    // InstanceExtension 検索
    uint32_t instanceExtensionCount = 0;
    vk::Bool32 surfaceExtFound = VK_FALSE;
    vk::Bool32 platformSurfaceExtFound = VK_FALSE;
    memset(extensionNames_, 0, sizeof(extensionNames_));

    auto result = vk::enumerateInstanceExtensionProperties(nullptr,
        &instanceExtensionCount,
        static_cast<vk::ExtensionProperties*>(nullptr));
    AE_BASE_ASSERT(result == vk::Result::eSuccess);

    if (0 < instanceExtensionCount) {
        std::unique_ptr<vk::ExtensionProperties[]> instance_extensions(
            new vk::ExtensionProperties[instanceExtensionCount]);
        result = vk::enumerateInstanceExtensionProperties(
            nullptr, &instanceExtensionCount, instance_extensions.get());
        AE_BASE_ASSERT(result == vk::Result::eSuccess);

        for (uint32_t i = 0; i < instanceExtensionCount; i++) {
            if (!std::strcmp(VK_KHR_SURFACE_EXTENSION_NAME,
                    instance_extensions[i].extensionName)) {
                surfaceExtFound = 1;
                extensionNames_[enabledExtensionCount_++] =
                    VK_KHR_SURFACE_EXTENSION_NAME;
            }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
            if (!std::strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
                    instance_extensions[i].extensionName)) {
                platformSurfaceExtFound = 1;
                extensionNames_[enabledExtensionCount_++] =
                    VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
            }
#elif defined(VK_USE_PLATFORM_METAL_EXT)
            if (!std::strcmp(VK_EXT_METAL_SURFACE_EXTENSION_NAME,
                    instance_extensions[i].extensionName)) {
                platformSurfaceExtFound = 1;
                extensionNames_[enabledExtensionCount_++] =
                    VK_EXT_METAL_SURFACE_EXTENSION_NAME;
            }
#endif
            AE_BASE_ASSERT_LESS(enabledExtensionCount_, ExtensionCountMax);
        }
    }

    if (!surfaceExtFound) {
        AE_BASE_ASSERT_NOT_REACHED_MSG(
            "vkEnumerateInstanceExtensionProperties failed to find "
            "the " VK_KHR_SURFACE_EXTENSION_NAME
            " extension.\n\n"
            "Do you have a compatible Vulkan installable client driver (ICD) "
            "installed?\n"
            "Please look at the Getting Started guide for additional "
            "information.\n");
    }

    if (!platformSurfaceExtFound) {
#if defined(VK_USE_PLATFORM_WIN32_KHR)
        AE_BASE_ASSERT_NOT_REACHED_MSG(
            "vkEnumerateInstanceExtensionProperties failed to find "
            "the " VK_KHR_WIN32_SURFACE_EXTENSION_NAME
            " extension.\n\n"
            "Do you have a compatible Vulkan installable client driver (ICD) "
            "installed?\n"
            "Please look at the Getting Started guide for additional "
            "information.\n");
#elif defined(VK_USE_PLATFORM_METAL_EXT)
        AE_BASE_ASSERT_NOT_REACHED(
            "vkEnumerateInstanceExtensionProperties failed to find "
            "the " VK_EXT_METAL_SURFACE_EXTENSION_NAME
            " extension.\n\nDo you have a compatible "
            "Vulkan installable client driver (ICD) installed?\nPlease "
            "look at the Getting Started guide for additional "
            "information.\n");
#endif
    }

    // インスタンス作成
    {
        auto const appInfo = ::vk::ApplicationInfo()
                                 .setPApplicationName("AdelEngineSample")
                                 .setApplicationVersion(0)
                                 .setPEngineName("AdelEngineSample")
                                 .setEngineVersion(0)
                                 .setApiVersion(VK_API_VERSION_1_0);
        auto const instInfo =
            ::vk::InstanceCreateInfo()
                .setPApplicationInfo(&appInfo)
                .setEnabledLayerCount(enabledLayerCount_)
                .setPpEnabledLayerNames(instanceValidationLayers)
                .setEnabledExtensionCount(enabledExtensionCount_)
                .setPpEnabledExtensionNames(extensionNames_);
        auto result = ::vk::createInstance(&instInfo, nullptr, &instance_);
        if (result == vk::Result::eErrorIncompatibleDriver) {
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "Cannot find a compatible Vulkan installable client driver "
                "(ICD).\n\n"
                "Please look at the Getting Started guide for additional "
                "information.\n");
        } else if (result == vk::Result::eErrorExtensionNotPresent) {
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "Cannot find a specified extension library.\n"
                "Make sure your layers path is set appropriately.\n");
        } else if (result != vk::Result::eSuccess) {
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "vkCreateInstance failed.\n\n"
                "Do you have a compatible Vulkan installable client driver "
                "(ICD) "
                "installed?\n"
                "Please look at the Getting Started guide for additional "
                "information.\n");
        }
    }

    // GPU列挙
    {
        uint32_t physicalDeviceCount;
        result = instance_.enumeratePhysicalDevices(
            &physicalDeviceCount, static_cast<vk::PhysicalDevice*>(nullptr));
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
        AE_BASE_ASSERT_MIN_TERM(
            1, int(physicalDeviceCount), PhysicalDeviceCountMax);
        result = instance_.enumeratePhysicalDevices(
            &physicalDeviceCount, physicalDevices_);
        AE_BASE_ASSERT(result == vk::Result::eSuccess);
    }
}

//------------------------------------------------------------------------------
System::~System() {
    // インスタンス破棄
    instance_.destroy(nullptr);
    instance_ = ::vk::Instance();

    // 複数作成防止
    AE_BASE_ASSERT(IsInstanceCreated);
    IsInstanceCreated = false;
}

//------------------------------------------------------------------------------
PhysicalDeviceInfo System::PhysicalDeviceInfo(
    const int physicalDeviceIndex) const {
    AE_BASE_ASSERT_LESS(physicalDeviceIndex, physicalDeviceCount_);
    gfx_low::PhysicalDeviceInfo info;

    const auto device = physicalDevices_[physicalDeviceIndex];

    // Queue 特性
    {
        const uint32_t queueFamilyCountMax = 8;
        VkQueueFamilyProperties queueFamilyProperties[queueFamilyCountMax] = {};
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(
            device,
            &queueFamilyCount,
            queueFamilyProperties);
        AE_BASE_ASSERT_LESS(queueFamilyCount, queueFamilyCountMax);

        for (uint32_t i = 0; i < queueFamilyCount; ++i) {
        }
    }

    return info;
}

//------------------------------------------------------------------------------
bool System::IsInstanceCreated = false;
}  // namespace gfx_low
}  // namespace ae
// EOF
