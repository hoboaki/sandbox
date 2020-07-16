// 文字コード：UTF-8
#pragma once

namespace ae {
namespace gfx_low {
class DeviceCreateInfo;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// グラフィックスデバイスを扱うクラス。
class Device {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    Device(const DeviceCreateInfo& createInfo);
    ~Device();
    //@}
};

}  // namespace gfx_low
}  // namespace ae
// EOF
