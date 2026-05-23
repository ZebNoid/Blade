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
    m_layoutRuntime->mount(rootWidget.tree());
}

auto App::initBackend() -> int
{
    if (!m_backend)
    {
        LOG_E(L"No Backend set");
        return -1;
    }
    m_backend->init();
    m_layoutRuntime = std::make_unique<LayoutRuntime>(
        m_backend.get()
    );
    m_backend->setResizeHandler(
        [this](Api::Id rootId, const Api::Size& size)
        {
            onNativeResize(rootId, size);
        }
    );
    return 0;
}

auto App::onNativeResize(
    Api::Id rootId,
    const Api::Size& size
) -> void
{
    if (!m_layoutRuntime)
    {
        return;
    }

    m_layoutRuntime->resizeRoot(
        rootId,
        size
    );
}


} // namespace
