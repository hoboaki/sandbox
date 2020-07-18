// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class SwapchainEntity;
}  // namespace gfx_low
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Swapchain にアクセスするハンドル。
/// @details
/// Swapchain 本体は SwapchainMaster が管理します。
/// ユーザーは SwapchainMaster で生成した SwapchainHandle に対して操作を行い、
/// 不要になったら SwapchainMaster に対して破棄要求を行います。
/// 
/// IsValid() == false なハンドルで各APIにアクセスした場合、アサーションエラーが発生します。
class SwapchainHandle {
public:
    /// @name コンストラクタ
    //@{
    /// 無効なハンドルを作成。
    SwapchainHandle() {}
    //@}

    /// @name ハンドルの状態
    //@{
    /// 有効なハンドルか。
    bool IsValid() const;
    //@}

    /// @name 内部処理用機能
    //@{
    static SwapchainHandle InternalCreate(SwapchainEntity* entity);
    SwapchainEntity& InternalEntity() const { return *entity_; }
    //@}

private:
    ::ae::base::Pointer<SwapchainEntity> entity_;

    /// 生成時の UniqueId。IsValid() 判定で使用。
    uint32_t entityUniqueId_ = 0;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
