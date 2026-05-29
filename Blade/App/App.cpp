#include "App.h"

#include "Common/Logger.h"


namespace Blade {

App* App::s_current = nullptr;

auto App::run() -> int
{
    s_current = this;

    onSetup();
    if (const auto code = initBackend(); code < 0)
    {
        if (s_current == this) s_current = nullptr;
        return code;
    }

    onCreate();

    const auto result = m_backend->runApp();
    if (s_current == this) s_current = nullptr;
    return result;
}

auto App::Quit() -> void
{
    Process({ .command = Api::AppCommandType::Quit });
}

auto App::DestroyRoot(Api::Id rootId) -> void
{
    Process({ .command = Api::AppCommandType::DestroyRoot, .target = rootId });
}

auto App::mountRoot(const RootWidget& rootWidget) -> Api::Id
{
    auto tree = rootWidget.tree();

    auto& root = m_layoutRuntime->mount(std::move(tree));

    m_eventRuntime.registerTree(root);
    return root.id;
}

auto App::MountRoot(const RootWidget& rootWidget) -> Api::Id
{
    if (!s_current)
    {
        LOG_W(L"RootWidget::mount called without active App");
        return Api::InvalidId;
    }

    return s_current->mountRoot(rootWidget);
}

auto App::initBackend() -> int
{
    if (!m_backend)
    {
        LOG_E(L"No Backend set");
        return -1;
    }
    m_backend->init();
    m_layoutRuntime = std::make_unique<LayoutRuntime>(m_backend.get(), m_trees);
    m_rootLifecycle = std::make_unique<RootLifecycle>(m_backend.get(), m_trees, m_eventRuntime, *m_layoutRuntime);
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

    if (message.type == Api::BackendMessageType::Destroyed)
    {
        const auto* destroyed = std::get_if<Api::BackendDestroyed>(&message.payload);
        if (destroyed && m_rootLifecycle) m_rootLifecycle->destroyRoot(destroyed->target);
        return {};
    }

    return {};
}

auto App::Process(Api::AppCommand command) -> void
{
    if (!s_current) return;

    if (command.command == Api::AppCommandType::Quit)
    {
        if (s_current->m_rootLifecycle) s_current->m_rootLifecycle->quit();
        return;
    }

    if (command.command == Api::AppCommandType::DestroyRoot)
    {
        if (s_current->m_rootLifecycle) s_current->m_rootLifecycle->destroyRoot(command.target);
        return;
    }

    if (s_current && s_current->m_backend)
    {
        s_current->m_backend->process(command);
    }
}

} // namespace
