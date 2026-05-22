#pragma once
#include "Api/ApiBackend.h"
#include "Node/NativeNode/NativeNode.h"
#include "WinApi/Window/NativeWindow.h"


namespace Blade::Backend {

class AppBackend;


class CommandDispatcher
{
public:
    explicit CommandDispatcher(AppBackend* backend);

    auto dispatch(
        const Api::BackendCommand& command
    ) -> void;

private:
    auto create(
        const Api::BackendCommand& command
    ) -> void;

    auto attach(
        const Api::BackendCommand& command
    ) -> void;

    auto remove(
        const Api::BackendCommand& command
    ) -> void;

    // TODO remove
    auto attachNative(
        NativeNode& parent,
        NativeNode& child
    ) -> void;

private:
    AppBackend* m_backend = nullptr;
};


} // namespace
