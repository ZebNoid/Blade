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

auto HitSurface(AppBackend& backend, Api::Point point, bool requireDrop = false) -> SurfaceHit;
auto HitId(const SurfaceHit& hit) -> Api::Id;
auto SurfaceById(AppBackend& backend, Api::Id id) -> SurfaceHit;

} // namespace Blade::Backend
