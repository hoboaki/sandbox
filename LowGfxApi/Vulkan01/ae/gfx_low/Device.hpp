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
/// @details
/// １つの Device オブジェクトで１つのGPUを扱います。
/// １つのアプリケーションで複数のGPUを扱う場合は複数のDeviceを作ります。
/// Device は作成時に Queue も内部で作成するため、
/// コンストラクタで渡す DeviceCreateInfo を通じて Queue の作成情報も渡します。
class Device {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    Device(const DeviceCreateInfo& createInfo);
    ~Device();
    //@}

    /// @name プロパティ
    //@{
    ///  コンストラクタで渡した System オブジェクト。
    gfx_low::System& System() const { return system_; }

    /// コンストラクタで渡した PhysicalDeviceIndex。
    int PhysicalDeviceIndex() const { return physicalDeviceIndex_; }
    //@}

    /// @name 内部処理用API
    //@{
    ::vk::Device& InternalInstance() { return device_; }
    //@}

private:
    gfx_low::System& system_;
    ::vk::Device device_;
    int physicalDeviceIndex_;
    ::ae::base::RuntimeArray<Queue*> queues_;

};

}  // namespace gfx_low
}  // namespace ae
// EOF
