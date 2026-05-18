#pragma once

#include <memory>

#include "Materializer/Materializer.h"
#include "WidgetsProps/Window/WindowProps.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsEvents/Window/WindowEvents.h"
#include "Windows/EventRouter/EventRouter.h"


namespace Blade {


class Window
{
protected:
    // Window(AppContext& appCtx, class WindowManager& manager);

    auto create() -> void
    {
        // WidgetContext w_ctx{
        //     nullptr,
        //     &m_appCtx,
        //     this
        // };
        //
        // m_native.create(w_ctx, this, m_props);
    }


    auto router() -> EventRouter& { return m_router; }

public:
    Window() {}

    Window(std::unique_ptr<Widget> child) {
        m_root = std::move(child);
    }

    template<typename TWidget>
    requires std::derived_from<TWidget, Widget>
    Window(TWidget child)
    {
        m_root = std::make_unique<TWidget>(
                std::move(child)
            );

        // auto& window = wm.NewWindow("BladeUI Window");
    }


    auto dispatchCommand(const WidgetId id, WidgetEvent event, const EventValue& value = {}) -> void
    {
        m_router.dispatchCommand(id, event, value);
    }

    // Window(const Window&) = delete;

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

protected:
    // auto setRoot(std::unique_ptr<Widget> root) -> Window&
    // {
    //     // m_root = std::move(root);
    //     //
    //     // WidgetContext ctx{
    //     //     m_native.handle(),
    //     //     &m_appCtx,
    //     //     this
    //     // };
    //     //
    //     // if (m_root == nullptr)
    //     // {
    //     //     // TODO error no root logger?
    //     //     return *this;
    //     // }
    //     //
    //     // m_materializer.mount(*m_root, ctx);
    //
    //     // TODO padding
    //     const auto [width, height] = m_native.clientSize();
    //
    //     m_root->measure({width, height}); // TODO
    //
    //     m_root->arrange({0, 0, width, height});
    //
    //     return *this;
    // }

private:
    // WinWindow m_native;
    Materializer m_materializer;
    EventRouter m_router;

    std::unique_ptr<Widget> m_root;

    WindowProps m_props{};
    WindowEvents m_events{};

    // friend class App;
    // friend class WindowManager;
    friend class Widget;
    // friend class WinWindow;
};


} // namespace
