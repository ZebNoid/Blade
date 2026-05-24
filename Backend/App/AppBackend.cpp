#include "AppBackend.h"

#include "CommandDispatcher/CommandDispatcher.h"
#include "WinApi/ClassRegistry/WindowClass.h"
#include "WinApi/CommonControls/CommonControls.h"


namespace Blade::Backend {


AppBackend::AppBackend()
    : m_hInstance(GetModuleHandle(nullptr))
      , m_dispatcher(this),
      m_factory(this)
{
}

auto AppBackend::init() -> void
{
    CommonControls::DpiAwareness();
    WindowClass::Init(m_hInstance);
}

auto AppBackend::runApp() -> int
{
    return m_runtime.run(
        [&]
        {
            m_host.destroyClosedWindows();

            if (m_host.count() == 0)
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

auto AppBackend::setResizeHandler(
    Api::ResizeHandler handler
) -> void
{
    m_resizeHandler = std::move(handler);
}

auto AppBackend::setEventHandler(
    Api::EventHandler handler
) -> void
{
    m_eventHandler = std::move(handler);
}

auto AppBackend::onWindowResize(
    Api::Id windowId,
    const Api::Size& size
) -> void
{
    if (m_resizeHandler)
    {
        m_resizeHandler(windowId, size);
    }
}

auto AppBackend::emitEvent(
    const Api::BackendEvent& event
) -> Api::EventResult
{
    if (!m_eventHandler)
    {
        return {};
    }

    return m_eventHandler(event);
}

auto AppBackend::eventHandler() -> Api::EventHandler*
{
    return &m_eventHandler;
}

auto AppBackend::process(const Api::BackendCommand& command) -> void
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
