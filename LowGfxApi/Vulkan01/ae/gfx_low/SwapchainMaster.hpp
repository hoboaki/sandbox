// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
class SwapchainMasterCreateInfo;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Swapchain の管理するクラス。
/// @details
/// Swapchain が使用するメモリ管理や、作り直し機能を提供する。
class SwapchainMaster {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    SwapchainMaster(const SwapchainMasterCreateInfo& createInfo);
    ~SwapchainMaster();
    //@}

private:
    Device& device_;
    ::vk::SurfaceKHR surface_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
