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
    /// 指定の QueueType をサポートしているか。
    bool isSupportedQueueType(QueueType queueType) const {
        return internalSupportQueueTypes.get(int(queueType));
    }

    // internal
    ::ae::base::BitSet<static_cast<int>(QueueType::TERM)>
        internalSupportQueueTypes;
    ::std::array<uint32_t, static_cast<int>(QueueType::TERM)>
        internalQueueFamilyIndexForQueueTypeArray;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
