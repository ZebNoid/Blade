#pragma once

#include "Api/ApiBackend.h"
#include "Runtime/EventRuntime/EventRuntime.h"
#include "Runtime/LayoutRuntime/LayoutRuntime.h"
#include "Runtime/RuntimeTree/RuntimeTree.h"


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

    auto onNativeResize(
        Api::Id rootId,
        const Api::Size& size
    ) -> void;

    auto onBackendEvent(
        const Api::BackendEvent& event
    ) -> Api::EventResult;

private:
    std::unique_ptr<Api::ApiBackend> m_backend;
    RuntimeTree m_runtimeTree;
    EventRuntime m_eventRuntime;
    std::unique_ptr<LayoutRuntime> m_layoutRuntime;

    friend class RootWidget;
};


} // namespace
