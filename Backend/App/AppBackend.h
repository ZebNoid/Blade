#pragma once

#include <windows.h>

#include "Api/ApiBackend.h"
#include "Node/NodeRegistry/NodeRegistry.h"
#include "WinApi/AppRuntime/AppRuntime.h"
#include "WinApi/WindowHost/WindowHost.h"

#include "CommandDispatcher/CommandDispatcher.h"

namespace Blade::Backend {


class AppBackend : public Api::ApiBackend
{
public:
    AppBackend();

    auto init() -> void override;

    auto runApp() -> int override;

    auto quit() -> void override;

    auto process(const Api::BackendCommand& command) -> void override;

    auto windows() -> WindowHost&;

    auto nodes() -> NodeRegistry&;

    auto testCreate() -> void;

private:
    HINSTANCE m_hInstance;

    AppRuntime m_runtime;

    WindowHost m_windows;// TODO rename m_windowHost

    NodeRegistry m_nodes;

    CommandDispatcher m_dispatcher;
};


} // namespace
