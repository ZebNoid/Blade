#pragma once

#include "../Windows/Window/Window.h"
#include "../Windows/WindowManager/WindowManager.h"


class App
{
public:
    App();
    virtual ~App() = default;

    auto run() -> int;

    template <typename T>
    auto window(T&& widget) -> Window&
    {
        // TODO name is sate after window created this is placeholder name
        auto& window = m_wm.newWindow("Blade Window");
        return window.setRoot(std::forward<T>(widget));
    }

    // TODO Alert / Popup
    static auto Alert(const std::string& text) -> void
    {
        // TODO Native alert builder
        MessageBox(nullptr, Utf8ToUtf16(text).c_str(), L"Help!", MB_OK);
    }
    virtual auto build() -> void {}

private:
    MSG m_msg = {};

protected:
    AppContext m_ctx{};

    WindowManager m_wm;

private:
    auto init() -> void;
};
