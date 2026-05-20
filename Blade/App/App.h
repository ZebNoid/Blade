#pragma once

#include "../../Api/Api/ApiBackend.h"


namespace Blade {


class App
{
public:
    virtual ~App() = default;

    auto run() -> int;

protected:
    template <typename TBackend>
        requires std::derived_from<std::decay_t<TBackend>, Api::ApiBackend>
    auto use(TBackend&& backend) -> void
    {
        m_backend = std::make_unique<std::decay_t<TBackend>>(
            std::forward<TBackend>(backend)
        );
    }

    virtual auto setup() -> void = 0;

    virtual auto ui() -> void = 0;

private:
    auto initBackend() -> void;

    auto buildUi() -> void;

private:
    std::unique_ptr<Api::ApiBackend> m_backend;
};


} // namespace
