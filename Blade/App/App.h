#pragma once

#include "Windows/Window/Window.h"
#include "Windows/WindowManager/WindowManager.h"
#include "Windows/WindowBuilder/WindowBuilder.h"


class App
{
public:
    App();
    virtual ~App() = default;

    auto run() -> int;

    template<typename T>
    auto window(T&& widget) -> WindowBuilder&
    {
        m_windowBuilders.emplace_back(
            std::forward<T>(widget)
        );

        return m_windowBuilders.back();
    }

    // TODO Alert / Popup
    static auto Alert(const std::string& text) -> void
    {
        // TODO Native alert builder
        MessageBox(nullptr, Utf8ToUtf16(text).c_str(), L"Help!", MB_OK);
    }

protected:
    virtual auto ui() -> void = 0;

private:
    auto build() -> void;

private:
    MSG m_msg = {};

protected:
    AppContext m_ctx{};

    WindowManager m_wm;

    std::vector<WindowBuilder> m_windowBuilders;

private:
    auto init() -> void;
};
