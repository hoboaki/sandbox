// 文字コード：UTF-8
#include <ae/gfx_low/SwapchainMaster.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/SwapchainMasterCreateInfo.hpp>
#include <ae/gfx_low/System.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
SwapchainMaster::SwapchainMaster(const SwapchainMasterCreateInfo& createInfo)
: device_(::ae::base::PtrToRef(createInfo.Device()))
, surface_() {
    // surface 作成
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {
        auto const surfaceCreateInfo =
            ::vk::Win32SurfaceCreateInfoKHR()
                .setHinstance(createInfo.Win32Hinstance())
                .setHwnd(createInfo.Win32Hwnd());

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
        VERIFY(result == vk::Result::eSuccess);
    }
#endif
}

//------------------------------------------------------------------------------
SwapchainMaster::~SwapchainMaster() {
    device_.System().InternalInstance().destroySurfaceKHR(surface_, nullptr);
    surface_ = ::vk::SurfaceKHR();
}

}  // namespace gfx_low
}  // namespace ae
// EOF
