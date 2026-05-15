#pragma once

#include <memory>

#include "../../Materializer/Materializer.h"
#include "../../Widgets/Widget/Widget.h"
#include "../../Native/NativeWindow/NativeWindow.h"
#include "../EventRouter/EventRouter.h"


class Window
{
public:
    Window(const Window&) = delete;

    auto show() -> void;

    auto title(const std::string& title) -> Window&
    {
        m_native.SetTitle(title);
        return *this;
    }

    auto size(const Size size) -> Window&
    {
        m_native.SetSize(size);
        return *this;
    }

protected:
    Window(AppContext& appCtx, class WindowManager& manager);

    auto Create(const std::string& title) -> void;

    auto OnDestroy() -> void;
    auto OnResize(Size size) -> void;

    auto Router() -> EventRouter& { return m_router; }

    auto DispatchCommand(const WidgetId id, WidgetEvent event, const EventValue& value = {}) -> void
    {
        m_router.DispatchCommand(id, event, value);
    }

private:
    template <typename T>
    auto SetRoot(T&& widget) -> Window&
    {
        using WidgetType = std::decay_t<T>;
        m_root = std::make_unique<WidgetType>(
            std::forward<T>(widget)
        );

        WidgetContext ctx{
            m_native.Handle(), // Set NativeWidget HWND
            &m_app_ctx,
            this
        };

        m_materializer.Mount(*m_root, ctx);

        if (m_root != nullptr)
        {
            const auto [width, height] = m_native.ClientSize();
            // First Arrange
            m_root->Arrange({0, 0, width, height});
        }

        return *this;
    }

private:
    WindowManager& m_manager;
    AppContext& m_app_ctx;

    NativeWindow m_native;
    Materializer m_materializer;
    EventRouter m_router;

    std::unique_ptr<Widget> m_root;

    friend class App; // App::Window возвращает ссылку на Window чтобы использовать метод Window::Title()
    friend class WindowManager;
    friend class Widget;
    friend class NativeWindow;
};
