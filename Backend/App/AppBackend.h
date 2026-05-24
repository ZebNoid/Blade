#pragma once

#include <windows.h>

#include "Api/ApiBackend.h"
#include "Node/NodeRegistry/NodeRegistry.h"
#include "WinApi/AppRuntime/AppRuntime.h"
#include "WindowHost/WindowHost.h"

#include "CommandDispatcher/CommandDispatcher.h"
#include "Node/NativeNodeFactory/NativeNodeFactory.h"


namespace Blade::Backend {


class AppBackend : public Api::ApiBackend
{
public:
    AppBackend();

    // -- non movable
    AppBackend(const AppBackend&) = delete;

    auto operator=(const AppBackend&) -> AppBackend& = delete;

    AppBackend(AppBackend&&) = delete;

    auto operator=(AppBackend&&) -> AppBackend& = delete;

    // -- non movable


    auto init() -> void override;

    auto runApp() -> int override;

    auto quit() -> void override;

    auto setResizeHandler(
        Api::ResizeHandler handler
    ) -> void override;

    auto setEventHandler(
        Api::EventHandler handler
    ) -> void override;

    auto onWindowResize(
        Api::Id windowId,
        const Api::Size& size
    ) -> void;

    auto emitEvent(
        const Api::BackendEvent& event
    ) -> Api::EventResult;

    auto eventHandler() -> Api::EventHandler*;

    auto process(const Api::BackendCommand& command) -> void override;

    auto host() -> WindowHost&;

    auto nodes() -> NodeRegistry&;

    auto factory() -> NativeNodeFactory&;

    auto handle() -> HINSTANCE;

private:
    HINSTANCE m_hInstance;

    AppRuntime m_runtime;

    WindowHost m_host;

    NodeRegistry m_nodes;

    CommandDispatcher m_dispatcher;

    NativeNodeFactory m_factory;

    Api::ResizeHandler m_resizeHandler;
    Api::EventHandler m_eventHandler;
};


} // namespace
