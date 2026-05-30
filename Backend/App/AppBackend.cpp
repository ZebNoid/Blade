#include "AppBackend.h"

#include "CommandDispatcher/CommandDispatcher.h"
#include "Common/Logger.h"
#include "WinApi/Window/WindowClass/WindowClass.h"
#include "WinApi/Display/DisplayApi/DisplayApi.h"


namespace Blade::Backend {


AppBackend::AppBackend()
    : m_hInstance(GetModuleHandle(nullptr))
    , m_dispatcher(this)
    , m_appDispatcher(this)
    , m_renderDispatcher(this)
    , m_factory(this)
{
}

auto AppBackend::init() -> void
{
    m_ole.init();
    DisplayApi::InitDpi();
    WindowClass::Init(m_hInstance);
}

auto AppBackend::runApp() -> int
{
    return m_runtime.run(
        [&]
        {
            m_host.destroyClosedWindows();
        }
    );
}

auto AppBackend::quit() -> void
{
    m_runtime.quit();
}

auto AppBackend::setMessageHandler(Api::BackendMessageHandler handler) -> void
{
    m_messageHandler = std::move(handler);
}

auto AppBackend::onWindowResize(Api::Id windowId, const Api::Size& size) -> void
{
    if (m_messageHandler)
    {
        m_messageHandler({
            .type = Api::BackendMessageType::Resize,
            .payload = Api::BackendResize{
                .target = windowId,
                .size = size
            }
        });
    }
}

auto AppBackend::emitEvent(const Api::BackendEvent& event) -> Api::EventResult
{
    if (!m_messageHandler)
    {
        return {};
    }

    return m_messageHandler({
        .type = Api::BackendMessageType::Event,
        .payload = event
    });
}

auto AppBackend::messageHandler() -> Api::BackendMessageHandler*
{
    return &m_messageHandler;
}

auto AppBackend::process(const Api::ElementCommand& command) -> void
{
    m_dispatcher.dispatch(command);
}

auto AppBackend::process(const Api::AppCommand& command) -> void
{
    m_appDispatcher.dispatch(command);
}

auto AppBackend::process(const Api::RenderCommand& command) -> void
{
    m_renderDispatcher.dispatch(command);
}

auto AppBackend::host() -> WindowHost&
{
    return m_host;
}

auto AppBackend::nodes() -> NodeRegistry&
{
    return m_nodes;
}

auto AppBackend::renderNodes() -> RenderRegistry&
{
    return m_renderNodes;
}

auto AppBackend::factory() -> NativeNodeFactory&
{
    return m_factory;
}

auto AppBackend::resources() -> ResourceManager&
{
    return m_resources;
}

auto AppBackend::handle() -> HINSTANCE
{
    return m_hInstance;
}

} // namespace
