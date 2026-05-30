#pragma once

#include <windows.h>

#include "Api/ApiBackend.h"
#include "Node/NativeBindingRegistry/NativeBindingRegistry.h"
#include "Node/NodeRegistry/NodeRegistry.h"
#include "Render/RenderCommandDispatcher/RenderCommandDispatcher.h"
#include "Render/RenderRegistry/RenderRegistry.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/AppRuntime/AppRuntime.h"
#include "WinApi/Interop/OleScope/OleScope.h"
#include "WindowHost/WindowHost.h"

#include "CommandDispatcher/CommandDispatcher.h"
#include "AppCommandDispatcher/AppCommandDispatcher.h"
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

    auto quit() -> void;

    auto setMessageHandler(Api::BackendMessageHandler handler) -> void override;

    auto onWindowResize(Api::Id windowId, const Api::Size& size) -> void;

    auto emitEvent(const Api::BackendEvent& event) -> Api::EventResult;

    auto messageHandler() -> Api::BackendMessageHandler*;

    auto process(const Api::ElementCommand& command) -> void override;

    auto process(const Api::AppCommand& command) -> void override;

    auto process(const Api::RenderCommand& command) -> void override;

    auto host() -> WindowHost&;

    auto nodes() -> NodeRegistry&;

    auto renderNodes() -> RenderRegistry&;

    auto factory() -> NativeNodeFactory&;

    auto resources() -> ResourceManager&;

    auto handle() -> HINSTANCE;

    auto bind(Api::WidgetType widget, Api::ComponentType component) -> void;

    auto bind(const NativeBindings& bindings) -> void;

    auto defaultBindings() const -> std::vector<NativeBindingInfo>;

    auto supportedComponents() const -> std::vector<ComponentInfo>;

private:
    HINSTANCE m_hInstance;

    AppRuntime m_runtime;
    OleScope m_ole;

    WindowHost m_host;

    NodeRegistry m_nodes;
    ResourceManager m_resources;

    CommandDispatcher m_dispatcher;

    AppCommandDispatcher m_appDispatcher;

    RenderCommandDispatcher m_renderDispatcher;

    NativeNodeFactory m_factory;

    RenderRegistry m_renderNodes;

    Api::BackendMessageHandler m_messageHandler;
};


} // namespace
