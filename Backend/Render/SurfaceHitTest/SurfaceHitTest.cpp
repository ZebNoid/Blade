#include "SurfaceHitTest.h"

#include "App/AppBackend.h"
#include "Components/RenderSurface/RenderSurface.h"
#include "Node/NativeNode/NativeNode.h"

namespace Blade::Backend {

namespace Surface::HitTest {

namespace {

template <typename Filter>
auto Find(AppBackend& backend, Api::Point point, Filter filter) -> SurfaceHit
{
    SurfaceHit result;
    int resultOrder = -1;

    backend.nodes().forEach(
        [&](NativeNode& node)
        {
            auto* surface = dynamic_cast<RenderSurface*>(node.native.get());
            if (!surface || !surface->hitTest(point)) return;

            if (!filter(*surface)) return;

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

} // namespace

auto Hit(AppBackend& backend, Api::Point point, bool requireDrop) -> SurfaceHit
{
    return Find(
        backend,
        point,
        [requireDrop](const RenderSurface& surface)
        {
            return !requireDrop || surface.wantsDrop();
        }
    );
}

auto ContextMenu(AppBackend& backend, Api::Point point, Api::MenuTrigger trigger) -> SurfaceHit
{
    return Find(
        backend,
        point,
        [trigger](const RenderSurface& surface)
        {
            return surface.hasContextMenu(trigger);
        }
    );
}

auto Id(const SurfaceHit& hit) -> Api::Id
{
    return hit.valid() ? hit.id : Api::InvalidId;
}

auto ById(AppBackend& backend, Api::Id id) -> SurfaceHit
{
    const auto* node = backend.nodes().get(id);
    if (!node) return {};

    auto* surface = dynamic_cast<RenderSurface*>(node->native.get());
    return {id, surface};
}

} // namespace Surface::HitTest

} // namespace Blade::Backend
