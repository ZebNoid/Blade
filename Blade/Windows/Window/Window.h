#pragma once

#include <memory>

#include "../../Materializer/Materializer.h"
#include "../../Widgets/Widget/Widget.h"
#include "../../Native/NativeWindow/NativeWindow.h"
#include "../EventRouter/EventRouter.h"
#include "Props/Window/WindowProps.h"


class Window
{
protected:
    Window(AppContext& appCtx, class WindowManager& manager);

    auto create(const std::string& title) -> void;

    auto onDestroy() -> void;
    auto onResize(Size size) -> void;

    auto router() -> EventRouter& { return m_router; }

    auto dispatchCommand(const WidgetId id, WidgetEvent event, const EventValue& value = {}) -> void
    {
        m_router.dispatchCommand(id, event, value);
    }

public:
    Window(const Window&) = delete;

    auto show() -> void;

    auto set(WindowProps props) -> Window&
    {
        m_props = std::move(props);
        return *this;
    }

private:
    template <typename T>
    auto setRoot(T&& widget) -> Window&
    {
        using WidgetType = std::decay_t<T>;
        m_root = std::make_unique<WidgetType>(
            std::forward<T>(widget)
        );

        WidgetContext ctx{
            m_native.handle(), // Set NativeWidget HWND
            &m_appCtx,
            this
        };

        m_materializer.mount(*m_root, ctx);

        if (m_root != nullptr)
        {
            const auto [width, height] = m_native.clientSize();
            // First Arrange
            m_root->arrange({0, 0, width, height});
        }

        return *this;
    }

private:
    WindowManager& m_manager;
    AppContext& m_appCtx;

    NativeWindow m_native;
    Materializer m_materializer;
    EventRouter m_router;

    std::unique_ptr<Widget> m_root;

    WindowProps m_props{};

    friend class App; // App::Window возвращает ссылку на Window чтобы использовать метод Window::Title()
    friend class WindowManager;
    friend class Widget;
    friend class NativeWindow;
};
