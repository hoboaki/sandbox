// 文字コード：UTF-8
#include <ae/gfx_low/QueueCreateInfo.hpp>

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
QueueCreateInfo& QueueCreateInfo::SetType(const QueueType type) {
    AE_BASE_ASSERT_ENUM(QueueType, type);
    type_ = type;
    return *this;
}

//------------------------------------------------------------------------------
QueueCreateInfo& QueueCreateInfo::SetPriority(const QueuePriority priority) {
    AE_BASE_ASSERT_ENUM(QueuePriority, priority);
    priority_ = priority;
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
