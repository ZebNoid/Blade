#pragma once

#include "../../Api/Api/ApiBackend.h"
#include "Api/WidgetTree.h"
#include "Runtime/Materializer/Materializer.h"


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

    virtual auto ui() -> Api::WidgetTree = 0;

private:
    auto initBackend() -> void;

    auto materialize() -> void;

private:
    std::unique_ptr<Api::ApiBackend> m_backend;
    Materializer m_materializer;
    // TODO remove
    std::vector<Api::BackendCommand> m_commands;
};


} // namespace
