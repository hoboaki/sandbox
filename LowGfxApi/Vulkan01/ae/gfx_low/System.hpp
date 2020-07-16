// 文字コード：UTF-8
#pragma once

#include <ae/base/IAllocator.hpp>
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
    /// 認識している物理デバイス数。
    int PhysicalDeviceCount() const { return physicalDeviceCount_; }

    /// 指定の物理デバイスの情報を取得。
    /// @param physicalDeviceIndex [0, PhysicalDeviceCount())
    PhysicalDeviceInfo PhysicalDeviceInfo(int physicalDeviceIndex) const;

    /// 全物理デバイスの情報をコンソールにダンプする。
    void DumpAllPhysicalDeviceInfo() const;
    //@}

    /// @name 内部処理用
    //@{
    ::ae::base::IAllocator& internalObjectAllocator() const {
        return objectAllocator_;
    }
    ::ae::base::IAllocator& internalTempWorkAllocator() const {
        return tempWorkAllocator_;
    }
    //@}

private:
    static const int PhysicalDeviceCountMax = 16;
    static const int ExtensionCountMax = 64;
    static const int LayerCountMax = 64;

    static bool IsInstanceCreated;

    ::ae::base::IAllocator& objectAllocator_;
    ::ae::base::IAllocator& tempWorkAllocator_;
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
