// 文字コード：UTF-8
#include <ae/base/RuntimeAssert.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
SystemCreateInfo::SystemCreateInfo() {}

//------------------------------------------------------------------------------
SystemCreateInfo& SystemCreateInfo::SetDebugLevel(
    const SystemDebugLevel level) {
    AE_BASE_ASSERT_ENUM(SystemDebugLevel, level);
    debugLevel_ = level;
    return *this;
}

//------------------------------------------------------------------------------
SystemCreateInfo& SystemCreateInfo::SetObjectAllocator(
    ::ae::base::IAllocator* allocator) {
    objectAllocator_.reset(allocator);
    return *this;
}

//------------------------------------------------------------------------------
SystemCreateInfo& SystemCreateInfo::SetTempWorkAllocator(
    ::ae::base::IAllocator* allocator) {
    tempWorkAllocator_.reset(allocator);
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
