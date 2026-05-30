#pragma once

#include "Common/CaptionProps.h"
#include "Common/Property.h"
#include "Common/Rect.h"
#include "Common/Size.h"
#include "Common/Types.h"
#include "Common/WindowPlacementProps.h"
#include "Common/WindowState.h"

namespace Blade::Backend {

struct NativeWindowPropsData
{
    const Api::Text* icon{};
    const Api::Rect* rect{};
    const Api::Size* size{};
    const Api::CaptionProps* caption{};
    const Api::WindowPlacementProps* placement{};
    const bool* resizable{};
    const bool* topMost{};
    const bool* taskbar{};
    const bool* visible{};
    const Api::Size* minSize{};
    const Api::Size* maxSize{};
    const Api::WindowState* state{};
    const Api::ContextMenus* contextMenus{};

    static auto Read(const Api::PropertyMap& propertyMap) -> NativeWindowPropsData;
    static auto RemoveHandled(Api::PropertyMap& propertyMap) -> void;

    auto isNormal() const -> bool;
};

} // namespace Blade::Backend
