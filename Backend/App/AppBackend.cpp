#include "AppBackend.h"

#include "WinApi/ClassRegistry/WindowClass.h"
#include "CommandDispatcher/CommandDispatcher.h"
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
    m_host.init(m_hInstance);
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

} // namespace
