#pragma once

#include "Api/ApiBackend.h"
#include "Api/WidgetTree.h"
#include "Runtime/Materializer/Materializer.h"


namespace Blade {


class App
{
public:
    virtual ~App() = default;

    auto run() -> int;

    auto addToTree(const Api::WidgetTree& widgetTree) -> void;

protected:
    template <typename TBackend, typename... Args>
        requires std::derived_from<TBackend, Api::ApiBackend>
    auto use(Args&&... args) -> void
    {
        m_backend = std::make_unique<TBackend>(
            std::forward<Args>(args)...
        );
    }

    virtual auto setup() -> void = 0;

    virtual auto buildUi() -> Api::WidgetTree = 0; // TODO remove

    virtual auto ui() -> void = 0;

private:
    auto initBackend() -> void;

    auto materialize() -> void;

private:
    std::unique_ptr<Api::ApiBackend> m_backend;
    Materializer m_materializer;

    Api::WidgetTree m_rootTree{.type = L"Root"};
};


} // namespace
