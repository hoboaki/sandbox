// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae {
namespace gfx_low {
class SwapchainMaster;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Swapchain オブジェクト作成時に必要な情報。
class SwapchainCreateInfo {
public:
    /// @name スワップチェインが抱えるイメージの枚数（設定できる値:1以上、初期値：2）
    //@{
    int ImageCount() const { return imageCount_;  }
    SwapchainCreateInfo& SetImageCount(int imageCount);
    //@}

private:
    ::ae::base::Pointer<gfx_low::SwapchainMaster> swapchainMaster_;
    int imageCount_ = 2;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
