// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkInclude.hpp>

namespace ae {
namespace gfx_low {
struct SystemCreateInfo;
}}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// グラフィックスライブラリシステムを扱うクラス。
/// @details
/// 何よりも最初にインスタンス化する必要があるオブジェクト。
/// ２つ以上作ることはできない。
/// このクラスの生成後、Device 等の生成をしてグラフィックス機能を扱える状態にしていく。
class System {
public:
	/// @name コンストラクタとデストラクタ
	//@{
    System(const SystemCreateInfo& createInfo);
	//@}

private:
    ::vk::Instance* instance_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
