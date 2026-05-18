#pragma once

#include "Api/AppBackend.h"
#include "Windows/Window/Window.h"
#include "Windows/WindowBuilder/WindowBuilder.h"
#include "Windows/WindowManager/WindowManager.h"


namespace Blade {


class App
{
public:
    App();

    virtual ~App() = default;

    template <typename TBackend>
    auto use() -> void
    {
        m_backend = std::make_unique<TBackend>();
    }

    auto run() -> int;

    // TODO remove USE Windows(...).start(this) or? .app(this) .bind(this) .init(this) not .set({app=this})
    template <typename T>
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
    virtual auto setup() -> void = 0;

    virtual auto ui() -> void = 0;

    virtual auto uiLoop() -> void
    {
    }

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

    std::unique_ptr<AppBackend> m_backend;
};


} // namespace
