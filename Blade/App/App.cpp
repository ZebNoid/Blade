#include "App.h"


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
    materialize(rootWidget.buildTree());
}

auto App::initBackend() -> int
{
    if (!m_backend)
    {
        std::cerr << "No Backend set" << std::endl;
        return -1;
    }
    m_backend->init();
    return 0;
}

auto App::materialize(const Api::WidgetTree& tree) -> void
{
    auto commands = m_materializer.build(tree);

    for (auto& cmd : commands)
    {
        m_backend->process(cmd);
    }
}


} // namespace
