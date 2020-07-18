// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/base/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// SwapchainMaster オブジェクト作成に必要な情報。
class SwapchainMasterCreateInfo {
public:
    /// @name 属する Device オブジェクトのポインタ（設定必須、初期値：nullptr）
    //@{
    gfx_low::Device* Device() const { return device_.get(); }
    SwapchainMasterCreateInfo& SetDevice(gfx_low::Device* system) {
        device_.reset(system);
        return *this;
    }
    //@}

    /// @name 実装ライブラリ固有の拡張情報（初期値：nullptr）
    //@{
    void* ExtInfoPtr() { return extInfoPtr_; }
    SwapchainMasterCreateInfo& SetExtInfoPtr(void* ptr) { extInfoPtr_ = ptr; }
    //@}

#if defined(AE_BASE_OS_WINDOWS)
    /// @name Windows 専用設定
    //@{
    HINSTANCE Win32Hinstance() const { return hinstance_; }
    HWND Win32Hwnd() const { return hwnd_; }
    SwapchainMasterCreateInfo& SetWin32Props(HINSTANCE hinstance, HWND hwnd) {
        hinstance_ = hinstance;
        hwnd_ = hwnd;
        return *this;
    }
    //@}
#endif

    // メモ：
    // 将来的に、Swapchain が確保しうる最大バッファ情報などをここに入れる。
    // そうしておくと SwapchainMaster 生成時に Swapchain
    // のバッファをあらかじめ確保でき Swapchain
    // を作りなおしが発生してもメモリ断片化がおきなくなる。
    // 仮想アドレスがあれば気にしなくてもいい説もあるけども、こういう設計ができる口は用意しておきたい。

private:
    ::ae::base::Pointer<gfx_low::Device> device_;
    void* extInfoPtr_;
#if defined(AE_BASE_OS_WINDOWS)
    HINSTANCE hinstance_ = nullptr;
    HWND hwnd_ = nullptr;
#endif
};

}  // namespace gfx_low
}  // namespace ae
// EOF
