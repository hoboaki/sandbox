// 文字コード：UTF-8
#include <ae/gfx_low/SystemCreateInfo.hpp>

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
SystemCreateInfo::SystemCreateInfo() {}

//------------------------------------------------------------------------------
void SystemCreateInfo::SetDebugLevel(const SystemDebugLevel level) {
    AE_BASE_ASSERT_ENUM(SystemDebugLevel, level);
    debugLevel_ = level;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
