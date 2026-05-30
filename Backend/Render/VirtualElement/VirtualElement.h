#pragma once

#include <windows.h>

#include "Common/Types.h"
#include "Geometry/Point.h"
#include "Menu/MenuTrigger.h"

namespace Blade::Backend {

class RenderRegistry;
class RenderSurface;
class ResourceManager;

struct VirtualElement
{
    Api::Id id = Api::InvalidId;
    RenderSurface* surface = nullptr;

    auto valid() const -> bool;
    auto paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) const -> void;
    auto hitTest(Api::Point point) const -> bool;
    auto wantsDrop() const -> bool;
    auto hasContextMenu(Api::MenuTrigger trigger) const -> bool;
    auto showContextMenu(Api::MenuTrigger trigger, POINT screenPoint) const -> bool;
    auto hover(RenderRegistry& renderNodes, bool hovered) const -> bool;
    auto dragOver(RenderRegistry& renderNodes, bool active) const -> bool;
    auto mouseDown(RenderRegistry& renderNodes) const -> bool;
    auto mouseUp(RenderRegistry& renderNodes) const -> bool;
    auto focus(RenderRegistry& renderNodes, bool focused) const -> bool;
};

} // namespace Blade::Backend
