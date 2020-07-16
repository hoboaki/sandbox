// 文字コード：UTF-8
#include <ae/gfx_low/Device.hpp>

#include <array>
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/gfx_low/DeviceCreateInfo.hpp>
#include <ae/gfx_low/PhysicalDeviceInfo.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/System.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
Device::Device(const DeviceCreateInfo& createInfo) {
    auto& system = ::ae::base::PtrToRef(createInfo.System());
    const auto physicalDeviceIndex = createInfo.PhysicalDeviceIndex();
    AE_BASE_ASSERT_MIN_TERM(
        0, physicalDeviceIndex, system.PhysicalDeviceCount());
    const auto physicalDeviceInfo =
        system.PhysicalDeviceInfo(physicalDeviceIndex);
    const auto queueCreateCount = createInfo.QueueCreateInfoCount();
    AE_BASE_ASSERT_LESS(0, queueCreateCount);
    const auto* queueCreateInfos = createInfo.QueueCrateInfos();
    AE_BASE_ASSERT_POINTER(queueCreateInfos);

#if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
    // Queue の作成数が上限を越えていないかのチェック
    {
        std::array<int, static_cast<int>(QueueType::TERM)> queueCounts;
        for (int i = 0; i < createInfo.QueueCreateInfoCount(); ++i) {
            ++queueCounts[int(createInfo.QueueCrateInfos()[i].Type())];
        }
        for (int i = 0; i < int(queueCounts.size()); ++i) {
            if (physicalDeviceInfo.creatableQueueCount(QueueType(i)) <
                queueCounts[i]) {
                AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
                    "Create queue count (for QueueType: %d) is too large.",
                    queueCounts[i]);
            }
        }
    }
#endif

    // デバイス作成
    //::ae::base::RuntimeArray<::vk::DeviceQueueCreateInfo> vulkanQueueCreateInfos(
    //    queueCreateCount, system.internalTempWorkAllocator()
    //    );
    //for (int i = 0; i < queueCreateCount; ++i) {
    //    auto& target = vulkanQueueCreateInfos[i];
    //}
}

//------------------------------------------------------------------------------
Device::~Device() {}

}  // namespace gfx_low
}  // namespace ae
// EOF
