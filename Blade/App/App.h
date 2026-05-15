#pragma once

#include "../Windows/Window/Window.h"
#include "../Windows/WindowManager/WindowManager.h"
#include "Windows/WindowBuilder/WindowBuilder.h"


class App
{
public:
    App();
    virtual ~App() = default;

    auto run() -> int;

    // TODO remove
    // template <typename T>
    // auto window(T&& widget) -> Window&
    // {
    //     auto& window = m_wm.newWindow("Blade Window");
    //     return window.setRoot(std::forward<T>(widget));
    // }

    template <typename T>
    auto window(T&& widget) -> WindowBuilder&
    {
        auto builder = std::make_unique<WindowBuilder>(
            std::forward<T>(widget)
        );

        auto& ref = *builder;

        m_windowBuilders.push_back(
            std::move(builder)
        );

        return ref;
    }

    // TODO Alert / Popup
    static auto Alert(const std::string& text) -> void
    {
        // TODO Native alert builder
        MessageBox(nullptr, Utf8ToUtf16(text).c_str(), L"Help!", MB_OK);
    }

protected:
    virtual auto build() -> void;

private:
    MSG m_msg = {};

protected:
    AppContext m_ctx{};

    WindowManager m_wm;

    std::vector<std::unique_ptr<WindowBuilder>> m_windowBuilders;

private:
    auto init() -> void;
};
