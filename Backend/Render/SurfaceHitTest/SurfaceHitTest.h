#pragma once

#include "Common/Types.h"
#include "Geometry/Point.h"

namespace Blade::Backend {

class AppBackend;
class RenderSurface;

struct SurfaceHit
{
    Api::Id id = Api::InvalidId;
    RenderSurface* surface = nullptr;

    auto valid() const -> bool { return surface != nullptr; }
};

namespace Surface::HitTest {
    auto Hit(AppBackend& backend, Api::Point point, bool requireDrop = false) -> SurfaceHit;
    auto Id(const SurfaceHit& hit) -> Api::Id;
    auto ById(AppBackend& backend, Api::Id id) -> SurfaceHit;
} // namespace Surface::HitTest

} // namespace Blade::Backend
