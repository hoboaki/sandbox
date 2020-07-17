// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeArray.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class DeviceCreateInfo;
class Queue;
class System;
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

private:
    System& system_;
    ::vk::Device device_;
    ::ae::base::RuntimeArray<Queue*> queues_;

};

}  // namespace gfx_low
}  // namespace ae
// EOF
