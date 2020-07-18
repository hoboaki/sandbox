// 文字コード：UTF-8
#include <ae/gfx_low/SwapchainHandle.hpp>

// includes
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/SwapchainEntity.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
bool SwapchainHandle::IsValid() const {
    return entity_.isValid() && entity_->uniqueId == entityUniqueId_;
}

//------------------------------------------------------------------------------
SwapchainHandle SwapchainHandle::InternalCreate(SwapchainEntity* entity) {
    SwapchainHandle result;
    result.entity_.set(::ae::base::PtrToRef(entity));
    result.entityUniqueId_ = entity->uniqueId;
    return result;
}

}  // namespace gfx_low
}  // namespace ae
// EOF
