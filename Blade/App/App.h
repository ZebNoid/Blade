#pragma once

#include "../Windows/WindowManager/WindowManager.h"
#include "../Windows/Window/Window.h"


class App
{
public:
    App();
    virtual ~App() = default;

    auto Run() -> int;

    template <typename T>
    auto window(T&& widget) -> Window&
    {
        // TODO name is sate after window created this is placeholder name
        auto& window = wm.NewWindow("Blade Window");
        return window.SetRoot(std::forward<T>(widget));
    }

    // TODO Alert / Popup
    static auto Alert(const std::string& text) -> void
    {
        // TODO Native alert builder
        MessageBox(nullptr, Utf8ToUtf16(text).c_str(), L"Help!", MB_OK);
    }

private:
    MSG msg = {};

protected:
    AppContext ctx{};

    WindowManager wm;

private:
    auto Init() -> void;
};
