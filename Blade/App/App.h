#pragma once

#include "Api/ApiBackend.h"
#include "Windows/WindowManager/WindowManager.h"


namespace Blade {


class App
{
public:
    virtual ~App() = default;

    template <typename TBackend>
    auto use() -> void
    {
        m_backend = std::make_unique<TBackend>();
    }

    template <typename TBackend>
    auto use(TBackend backend) -> void
    {
        m_backend = std::make_unique<TBackend>(std::move(backend));
    }

    auto run() -> int;

    auto wm() -> WindowManager&
    {
        return m_wm;
    }

    // TODO move to Backend Alert / Popup
    static auto Alert(const std::string& text) -> void
    {
        // TODO Native alert builder
        // MessageBox(nullptr, Utf8ToUtf16(text).c_str(), L"Help!", MB_OK);
    }

protected:
    virtual auto setup() -> void = 0;

    virtual auto ui() -> void = 0;

    // virtual auto uiLoop() -> void {    } // TODO app loop callback?

private:
    auto initBackend() -> void;

    auto buildUi() -> void;

protected:
    WindowManager m_wm;

private:
    std::unique_ptr<ApiBackend> m_backend;
};


} // namespace
