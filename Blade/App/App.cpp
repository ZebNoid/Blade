#include "App.h"

#include "Common/Logger.h"


namespace Blade {

auto App::run() -> int
{
    onSetup();
    if (const auto code = initBackend(); code < 0) return code;

    onCreate();

    return m_backend->runApp();
}

auto App::addToTree(const RootWidget& rootWidget) -> void
{
    auto tree = rootWidget.tree();

    m_runtimeTree.assignIds(tree);
    m_eventRuntime.registerTree(tree);

    m_layoutRuntime->mount(std::move(tree));
}

auto App::initBackend() -> int
{
    if (!m_backend)
    {
        LOG_E(L"No Backend set");
        return -1;
    }
    m_backend->init();
    m_layoutRuntime = std::make_unique<LayoutRuntime>(m_backend.get());
    m_backend->setMessageHandler(
        [this](const Api::BackendMessage& message)
        {
            return onBackendMessage(message);
        }
    );

    return 0;
}

auto App::onBackendMessage(const Api::BackendMessage& message) -> Api::EventResult
{
    if (message.type == Api::BackendMessageType::Resize)
    {
        const auto* resize = std::get_if<Api::BackendResize>(&message.payload);

        if (resize && m_layoutRuntime)
        {
            m_layoutRuntime->resizeRoot(resize->target, resize->size);
        }

        return {};
    }

    if (message.type == Api::BackendMessageType::Event)
    {
        const auto* event = std::get_if<Api::BackendEvent>(&message.payload);
        return event ? m_eventRuntime.dispatch(*event) : Api::EventResult{};
    }

    return {};
}


} // namespace
