#pragma once
#include <optional>

#include "Command/ElementCommand.h"
#include "Node/NativeCreateContext/NativeCreateContext.h"
#include "Node/NativeFactoryRegistry/NativeFactoryRegistry.h"
#include "Node/NativeNode/NativeNode.h"


namespace Blade::Backend {

class AppBackend;


class NativeNodeFactory
{
public:
    explicit NativeNodeFactory(AppBackend* backend);

    auto create(const Api::ElementCommand& command) -> std::optional<NativeNode>;

private:
    auto registerFactories() -> void;

    auto createWindow(const Api::ElementCommand& command) -> std::optional<NativeNode>;

    auto createButton(const Api::ElementCommand& command) -> std::optional<NativeNode>;

    auto createContextArea(const Api::ElementCommand& command) -> std::optional<NativeNode>;

    auto createLabel(const Api::ElementCommand& command) -> std::optional<NativeNode>;

    auto createTray(const Api::ElementCommand& command) -> std::optional<NativeNode>;

private:
    AppBackend* m_backend = nullptr;
    NativeCreateContext m_context;
    NativeFactoryRegistry m_registry;
};


} // namespace
