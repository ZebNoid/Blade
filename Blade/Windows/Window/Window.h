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

    Window(std::unique_ptr<Widget> child)
    {
        m_root = std::move(child);
    }

    template <typename TWidget>
        requires std::derived_from<TWidget, Widget>
    Window(TWidget child)
    {
        m_root = std::make_unique<TWidget>(
            std::move(child)
        );
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

    auto id(WidgetId& id) -> Window&
    {
        // TODO get id
        // id = m_id;
        return *this;
    }

    auto mount(class App* app) && -> void;

    auto root() const -> Widget*
    {
        return m_root.get();
    }

    // TODO friend WindowManager?
    auto getProps() -> WindowProps
    {
        return m_props;
    }

protected:
    // auto setRoot(std::unique_ptr<Widget> root) -> Window&
    // // TODO Window materializer mount
    //     // m_materializer.mount(*m_root, ctx);
    //
    //     // TODO padding
    //     const auto [width, height] = m_native.clientSize();
    //
    //     m_root->measure({width, height}); // TODO
    //
    //     m_root->arrange({0, 0, width, height});
    //     return *this;
    // }

private:
    App* m_app = nullptr;

    // WinWindow m_native;
    // Materializer m_materializer;
    EventRouter m_router;

    std::unique_ptr<Widget> m_root;

    WindowProps m_props{};
    WindowEvents m_events{};

    friend class Widget;
};


} // namespace
