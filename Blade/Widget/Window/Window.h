#pragma once

#include "WindowProps.h"
#include "WindowEvents.h"
#include "Base/RootWidget.h"
#include "Runtime/Normalize/Normalize.h"


namespace Blade {

class Window : public RootWidget<Window>
{
public:
    Window()
    {
        m_tree.type = Api::WidgetTypes::Window;
        Normalize::PropsMerge(m_tree, WindowProps{});
    }

    explicit Window(const WidgetNode& child)
    {
        m_tree.type = Api::WidgetTypes::Window;
        Normalize::PropsMerge(m_tree, WindowProps{});

        m_tree.children.push_back(
            child.tree()
        );
    }

    auto set(WindowProps props) -> Window&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto on(WindowEvents events) -> Window&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
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
};


} // namespace
