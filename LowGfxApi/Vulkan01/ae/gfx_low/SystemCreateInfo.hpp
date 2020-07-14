// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SystemDebugLevel.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// System オブジェクト作成に必要な情報。
class SystemCreateInfo {
public:
    /// @name コンストラクタ
    //@{
    SystemCreateInfo();
    //@}

    /// @name システムデバッグレベル（初期値：NoDebug）
    //@{
    SystemDebugLevel DebugLevel() const { return debugLevel_; }
    void SetDebugLevel(SystemDebugLevel level);
    //@}

private:
    SystemDebugLevel debugLevel_ = SystemDebugLevel::NoDebug;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
