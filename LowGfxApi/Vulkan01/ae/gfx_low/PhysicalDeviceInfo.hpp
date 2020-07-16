// 文字コード：UTF-8
#pragma once

#include <ae/base/BitSet.hpp>
#include <ae/gfx_low/QueueType.hpp>
#include <array>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// GPU デバイス情報。
class PhysicalDeviceInfo {
public:
    /// 指定の QueueType の Queue の作成可能最大数。。
    int creatableQueueCount(QueueType queueType) const {
        return internalCreatableQueueCounts[int(queueType)];
    }

    // internal
    ::std::array<int, static_cast<int>(QueueType::TERM)>
        internalCreatableQueueCounts = {};
};

}  // namespace gfx_low
}  // namespace ae
// EOF
