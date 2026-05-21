#pragma once

#include "Api/ApiBackend.h"
#include "Api/WidgetTree.h"
#include "Runtime/Materializer/Materializer.h"


namespace Blade {

class RootWidget;


class App
{
public:
    virtual ~App() = default;

    auto run() -> int;

protected:
    template <typename TBackend, typename... Args>
        requires std::derived_from<TBackend, Api::ApiBackend>
    auto use(Args&&... args) -> void
    {
        m_backend = std::make_unique<TBackend>(
            std::forward<Args>(args)...
        );
    }

    virtual auto onSetup() -> void = 0;

    virtual auto onCreate() -> void = 0;

protected:

private:
    auto addToTree(const RootWidget& rootWidget) -> void;

    auto initBackend() -> int;

    auto materialize(const Api::WidgetTree& tree) -> void;

private:
    std::unique_ptr<Api::ApiBackend> m_backend;
    Materializer m_materializer;

    friend class RootWidget;
};


} // namespace
