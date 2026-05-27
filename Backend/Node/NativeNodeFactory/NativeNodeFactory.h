#pragma once
#include <optional>

#include "Command/ElementCommand.h"
#include "Node/NativeNode/NativeNode.h"


namespace Blade::Backend {

class AppBackend;


class NativeNodeFactory
{
public:
    explicit NativeNodeFactory(AppBackend* backend);

    auto create(const Api::ElementCommand& command) -> std::optional<NativeNode>;

private:
    auto createWindow(const Api::ElementCommand& command) -> std::optional<NativeNode>;

    auto createButton(const Api::ElementCommand& command) -> std::optional<NativeNode>;

private:
    AppBackend* m_backend = nullptr;
};


} // namespace
