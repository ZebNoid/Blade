#pragma once

#include "Base/RootWidget.h"
#include "Fabric/WindowPlacement.h"
#include "Geometry/Size.h"
#include "Lifecycle/Lifetime.h"
#include "Window/CaptionProps.h"
#include "Window/WindowState.h"


namespace Blade {

class Window : public RootWidget<Window>
{
public:
    Window()
    {
        m_tree.type = Api::WidgetTypes::Window;
        initDefaults();
    }

    explicit Window(const WidgetNode& child)
    {
        m_tree.type = Api::WidgetTypes::Window;
        initDefaults();

        m_tree.children.push_back(
            child.tree()
        );
    }

    auto title(Api::Text title) -> Window&
    {
        m_tree.backend.create[Api::Props::Title] = std::move(title);
        return *this;
    }

    auto icon(Api::Text icon) -> Window&
    {
        m_tree.backend.create[Api::Props::Icon] = std::move(icon);
        return *this;
    }

    auto placement(Api::WindowPlacementProps placement) -> Window&
    {
        m_tree.backend.create[Api::Props::Placement] = placement;
        return *this;
    }

    auto resizable(bool value = true) -> Window&
    {
        m_tree.backend.create[Api::Props::Resizable] = value;
        return *this;
    }

    auto topMost(bool value = true) -> Window&
    {
        m_tree.backend.create[Api::Props::TopMost] = value;
        return *this;
    }

    auto taskbar(bool value = true) -> Window&
    {
        m_tree.backend.create[Api::Props::Taskbar] = value;
        return *this;
    }

    auto minSize(Api::Size size) -> Window&
    {
        m_tree.backend.create[Api::Props::MinSize] = size;
        return *this;
    }

    auto maxSize(Api::Size size) -> Window&
    {
        m_tree.backend.create[Api::Props::MaxSize] = size;
        return *this;
    }

    auto caption(Api::CaptionProps caption) -> Window&
    {
        m_tree.backend.create[Api::Props::Caption] = caption;
        return *this;
    }

    auto state(Api::WindowState state) -> Window&
    {
        m_tree.backend.create[Api::Props::State] = state;
        return *this;
    }

    auto lifetime(Api::Lifetime lifetime) -> Window&
    {
        m_tree.lifetime = lifetime;
        return *this;
    }

    auto onClose(Api::EventCallback callback) -> Window&
    {
        applyEvent(Api::Events::Close, std::move(callback));
        return *this;
    }

    auto onDrop(Api::EventCallback callback) -> Window&
    {
        applyEvent(Api::Events::Drop, std::move(callback));
        return *this;
    }

private:
    auto initDefaults() -> void
    {
        title(L"Blade");
        size({800, 600});
        placement(Api::WindowPlacement::Default());
        visible(true);
        resizable(true);
        topMost(false);
        taskbar(true);
        minSize({});
        maxSize({});
        caption({});
        state(Api::WindowState::Normal);
        lifetime(Api::Lifetime::Owner);
    }
};


} // namespace
