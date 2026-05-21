#pragma once
#include <optional>

#include "Api/BackendCommand.h"
#include "Node/NativeNode/NativeNode.h"


namespace Blade::Backend {

class AppBackend;


class NativeNodeFactory
{
public:
    explicit NativeNodeFactory(
        AppBackend* backend
    );

    auto create(
        const Api::BackendCommand& command
    ) -> std::optional<NativeNode>;

private:
    auto createWindow(
        const Api::BackendCommand& command
    ) -> std::optional<NativeNode>;

private:
    AppBackend* m_backend = nullptr;
};


} // namespace
