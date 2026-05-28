#include "AppBackend.h"

#include "CommandDispatcher/CommandDispatcher.h"
#include "WinApi/Window/WindowClass/WindowClass.h"
#include "WinApi/Display/DisplayApi/DisplayApi.h"


namespace Blade::Backend {


AppBackend::AppBackend()
    : m_hInstance(GetModuleHandle(nullptr))
    , m_dispatcher(this)
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
            m_nodes.collectGarbage();

            if (m_nodes.ownerCount() == 0)
            {
                quit();
            }
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
    m_dispatcher.dispatch(command); // With Error !
}

auto AppBackend::host() -> WindowHost&
{
    return m_host;
}

auto AppBackend::nodes() -> NodeRegistry&
{
    return m_nodes;
}

auto AppBackend::factory() -> NativeNodeFactory&
{
    return m_factory;
}

auto AppBackend::handle() -> HINSTANCE
{
    return m_hInstance;
}

} // namespace
