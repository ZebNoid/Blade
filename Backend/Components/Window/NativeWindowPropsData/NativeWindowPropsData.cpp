#include "NativeWindowPropsData.h"

#include "Property/PropertyReader.h"

namespace Blade::Backend {

auto NativeWindowPropsData::Read(const Api::PropertyMap& propertyMap) -> NativeWindowPropsData
{
    return {
        .icon = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Icon),
        .rect = PropertyReader::Get<Api::Rect>(propertyMap, Api::Props::Rect),
        .size = PropertyReader::Get<Api::Size>(propertyMap, Api::Props::Size),
        .caption = PropertyReader::Get<Api::CaptionProps>(propertyMap, Api::Props::Caption),
        .placement = PropertyReader::Get<Api::WindowPlacementProps>(propertyMap, Api::Props::Placement),
        .resizable = PropertyReader::Get<bool>(propertyMap, Api::Props::Resizable),
        .topMost = PropertyReader::Get<bool>(propertyMap, Api::Props::TopMost),
        .taskbar = PropertyReader::Get<bool>(propertyMap, Api::Props::Taskbar),
        .visible = PropertyReader::Get<bool>(propertyMap, Api::Props::Visible),
        .minSize = PropertyReader::Get<Api::Size>(propertyMap, Api::Props::MinSize),
        .maxSize = PropertyReader::Get<Api::Size>(propertyMap, Api::Props::MaxSize),
        .state = PropertyReader::Get<Api::WindowState>(propertyMap, Api::Props::State),
        .contextMenus = PropertyReader::Get<Api::ContextMenus>(propertyMap, Api::Props::ContextMenus),
    };
}

auto NativeWindowPropsData::RemoveHandled(Api::PropertyMap& propertyMap) -> void
{
    propertyMap.erase(Api::Props::Rect);
    propertyMap.erase(Api::Props::Size);
    propertyMap.erase(Api::Props::Icon);
    propertyMap.erase(Api::Props::Caption);
    propertyMap.erase(Api::Props::Placement);
    propertyMap.erase(Api::Props::Resizable);
    propertyMap.erase(Api::Props::TopMost);
    propertyMap.erase(Api::Props::Taskbar);
    propertyMap.erase(Api::Props::Visible);
    propertyMap.erase(Api::Props::MinSize);
    propertyMap.erase(Api::Props::MaxSize);
    propertyMap.erase(Api::Props::State);
    propertyMap.erase(Api::Props::ContextMenus);
    propertyMap.erase(Api::Props::Lifetime);
}

auto NativeWindowPropsData::isNormal() const -> bool
{
    return !state || *state == Api::WindowState::Normal;
}

} // namespace Blade::Backend
