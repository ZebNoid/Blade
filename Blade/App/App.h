#pragma once

#include "Api/ApiBackend.h"
#include "Runtime/EventRuntime/EventRuntime.h"
#include "Runtime/LayoutRuntime/LayoutRuntime.h"
#include "Runtime/WidgetTreeRegistry/WidgetTreeRegistry.h"


namespace Blade {

class RootWidget;


class App
{
public:
    virtual ~App() = default;

    auto run() -> int;
    static auto Quit() -> void;
    static auto CloseWindow(Api::Id windowId) -> void;
    static auto ShowWindow(Api::Id windowId) -> void;
    static auto HideWindow(Api::Id windowId) -> void;
    static auto MinimizeWindow(Api::Id windowId) -> void;
    static auto MaximizeWindow(Api::Id windowId) -> void;
    static auto RestoreWindow(Api::Id windowId) -> void;
    static auto SetTrayIcon(Api::Id trayId, Api::Text icon) -> void;
    static auto SetTrayTitle(Api::Id trayId, Api::Text title) -> void;
    static auto DestroyRoot(Api::Id rootId) -> void;

protected:
    template <typename TBackend, typename... Args>
        requires std::derived_from<TBackend, Api::ApiBackend>
    auto use(Args&&... args) -> void
    {
        m_backend = std::make_unique<TBackend>(std::forward<Args>(args)...);
    }

    virtual auto onSetup() -> void = 0;

    virtual auto onCreate() -> void = 0;

protected:

private:
    auto addToTree(const RootWidget& rootWidget) -> Api::Id;

    auto initBackend() -> int;

    auto onBackendMessage(const Api::BackendMessage& message) -> Api::EventResult;

    static auto Process(Api::AppCommand command) -> void;

private:
    static App* s_current;

    std::unique_ptr<Api::ApiBackend> m_backend;
    WidgetTreeRegistry m_trees;
    EventRuntime m_eventRuntime;
    std::unique_ptr<LayoutRuntime> m_layoutRuntime;

    friend class RootWidget;
};


} // namespace
