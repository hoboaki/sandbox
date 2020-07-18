// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class SwapchainMaster;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// スワップチェインの実体。
/// @details
/// 内部的に使用するクラスなのでユーザーは直接アクセスしないでください。
class SwapchainEntity {
public:
    /// 無効な UniqueId 値。
    static const int InvalidUniqueId = 0;

    /// 所属する SwapchainMaster のポインタ。
    ::ae::base::Pointer<SwapchainMaster> swapchainMaster;

    /// Swapchain の実装ライブラリオブジェクト。
    ::vk::SwapchainKHR swapchain;

    /// ユニークID。古くなった Handle の Valid 判定で使う。
    uint32_t uniqueId = InvalidUniqueId;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
