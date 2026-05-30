#include "WindowSurfaceHitTest.h"

#include "App/AppBackend.h"
#include "Components/RenderSurface/RenderSurface.h"
#include "Node/NativeNode/NativeNode.h"

namespace Blade::Backend {

auto HitSurface(AppBackend& backend, Api::Point point, bool requireDrop) -> SurfaceHit
{
    SurfaceHit result;
    int resultOrder = -1;

    backend.nodes().forEach(
        [&](NativeNode& node)
        {
            auto* surface = dynamic_cast<RenderSurface*>(node.native.get());
            if (!surface || !surface->hitTest(point)) return;

            if (requireDrop && !surface->wantsDrop()) return;

            const auto order = node.order;
            if (!result.valid() || order > resultOrder || (order == resultOrder && node.id > result.id))
            {
                result = {node.id, surface};
                resultOrder = order;
            }
        }
    );

    return result;
}

auto HitId(const SurfaceHit& hit) -> Api::Id
{
    return hit.valid() ? hit.id : Api::InvalidId;
}

auto SurfaceById(AppBackend& backend, Api::Id id) -> SurfaceHit
{
    const auto* node = backend.nodes().get(id);
    if (!node) return {};

    auto* surface = dynamic_cast<RenderSurface*>(node->native.get());
    return {id, surface};
}

} // namespace Blade::Backend
