#pragma once

#include <memory>

#include "WidgetsProps/Window/WindowProps.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsEvents/Window/WindowEvents.h"
#include "Windows/EventRouter/EventRouter.h"


namespace Blade {


class Window : public Widget
{
protected:
    auto router() -> EventRouter& { return m_router; }

public:
    Window() = default;

    // Window(std::unique_ptr<Widget> child)
    // {
    //     // m_root = std::move(child);
    // }

    // template <typename TWidget>
    //     requires std::derived_from<TWidget, Widget>
    template <typename TWidget>
    Window(TWidget child)
    {
        // m_root = std::make_unique<TWidget>(
        //     std::move(child)
        // );
    }


    auto name() -> std::wstring override { return L"Window"; }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override
    {
    }

    auto measure(Size available) -> Size override { return {0, 0}; }

    auto dispatchCommand(const WidgetId id, WidgetEvent event, const EventValue& value = {}) -> void
    {
        m_router.dispatchCommand(id, event, value);
    }

    auto show() -> void;

    auto destroy() -> void;

    auto resize(Size size) -> void;


    auto set(WindowProps props) & -> Window&
    {
        m_props = std::move(props);
        return *this;
    }

    auto set(WindowProps props) && -> Window&&
    {
        m_props = std::move(props);
        return std::move(*this);
    }

    auto on(WindowEvents events) -> Window&
    {
        m_events = std::move(events);
        return *this;
    }

    auto mount(class App* app) && -> void;

    // auto root() const -> Widget*
    // {
    //     return m_root.get();
    // }

    auto getProps() -> WindowProps
    {
        return m_props;
    }

private:
    App* m_app = nullptr;

    EventRouter m_router;

    // std::unique_ptr<Widget> m_root;

    WindowProps m_props{};
    WindowEvents m_events{};

    friend class Widget;
};


} // namespace
