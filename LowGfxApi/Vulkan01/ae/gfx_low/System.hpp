// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/base/Noncopyable.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
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

private:
    static bool IsInstanceCreated;

    ::vk::Instance instance_;
    uint32_t enabledExtensionCount_ = 0;
    uint32_t enabledLayerCount_ = 0;
    char const* extensionNames_[64] = {};
    char const* enabledLayers_[64] = {};
};

}  // namespace gfx_low
}  // namespace ae
// EOF
