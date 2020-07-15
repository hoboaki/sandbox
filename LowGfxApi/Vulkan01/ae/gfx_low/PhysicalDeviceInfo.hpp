// 文字コード：UTF-8
#pragma once

#include <ae/base/BitSet.hpp>
#include <ae/gfx_low/QueueType.hpp>

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
    ::ae::base::BitSet<static_cast<int>(QueueType::TERM)> internalSupportQueueTypes;
};

}
}  // namespace ae
// EOF
