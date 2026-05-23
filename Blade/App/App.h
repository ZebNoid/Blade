#pragma once

#include "Api/ApiBackend.h"
#include "Base/WidgetTree.h"
#include "Runtime/Materializer/Materializer.h"
#include <unordered_map>


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

    auto materialize(const WidgetTree& tree) -> void;

    auto updateLayout(
        const WidgetTree& tree,
        const Api::Size& size
    ) -> void;

    auto onNativeResize(
        Api::Id rootId,
        const Api::Size& size
    ) -> void;

private:
    std::unique_ptr<Api::ApiBackend> m_backend;
    Materializer m_materializer;
    std::unordered_map<Api::Id, WidgetTree> m_roots;

    friend class RootWidget;
};


} // namespace
