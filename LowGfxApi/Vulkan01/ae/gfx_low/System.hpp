// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/base/Noncopyable.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class PhysicalDeviceInfo;
class SystemCreateInfo;
}}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// グラフィックスライブラリシステムを扱うクラス。
/// @details
/// 何よりも最初にインスタンス化する必要があるオブジェクト。２つ以上作ることはできない。
/// このクラスの生成後、Device 等の生成をしてグラフィックス機能を扱える状態にしていく。
class System : base::Noncopyable<System> {
public:
	/// @name コンストラクタとデストラクタ
	//@{
    System(const SystemCreateInfo& createInfo);
    ~System();
	//@}

    /// @name 情報取得
    //@{
    int PhysicalDeviceCount() const { return physicalDeviceCount_; }
    PhysicalDeviceInfo PhysicalDeviceInfo(int physicalDeviceIndex) const;
    //@}

private:
    static const int PhysicalDeviceCountMax = 16;
    static const int ExtensionCountMax = 64;
    static const int LayerCountMax = 64;

    static bool IsInstanceCreated;

    ::vk::Instance instance_;
    int enabledExtensionCount_ = 0;
    int enabledLayerCount_ = 0;
    int physicalDeviceCount_ = 0;
    char const* extensionNames_[ExtensionCountMax] = {};
    char const* enabledLayers_[LayerCountMax] = {};
    ::vk::PhysicalDevice physicalDevices_[PhysicalDeviceCountMax] = {};
};

}  // namespace gfx_low
}  // namespace ae
// EOF
