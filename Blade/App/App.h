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

protected:
    virtual auto setup() -> void = 0;

    virtual auto ui() -> void = 0;

private:
    auto initBackend() -> void;

    auto buildUi() -> void;

protected:
    WindowManager m_wm;

private:
    std::unique_ptr<ApiBackend> m_backend;
};


} // namespace
