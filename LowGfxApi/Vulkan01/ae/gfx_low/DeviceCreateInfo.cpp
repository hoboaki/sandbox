// 文字コード：UTF-8
#include <ae/gfx_low/DeviceCreateInfo.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
DeviceCreateInfo& DeviceCreateInfo::SetSystem(gfx_low::System* system) {
    system_.reset(system);
    return *this;
}

//------------------------------------------------------------------------------
DeviceCreateInfo& DeviceCreateInfo::SetQueueCreateInfos(
    const int count, const QueueCreateInfo* infos) {
    queueCreateInfosCount_ = count;
    queueCreateInfos_.reset(infos);
    return *this;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
