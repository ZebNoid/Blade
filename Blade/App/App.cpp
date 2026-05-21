#include "App.h"


namespace Blade {

auto App::run() -> int
{
    setup();
    if (!m_backend)
    {
        std::cerr << "No Backend set" << std::endl;
        return -1;
    }
    initBackend();

    ui();

    materialize();

    return m_backend->runApp();
}

auto App::addToTree(const Api::WidgetTree& widgetTree) -> void
{
    m_rootTree.children.push_back(widgetTree);
}

auto App::initBackend() -> void
{
    m_backend->init();
}

auto App::materialize() -> void
{
    // const auto tree = buildUi();
    const auto tree = m_rootTree;
    auto commands = m_materializer.build(tree);

    for (auto& cmd : commands)
    {
        m_backend->process(cmd);
    }
}


} // namespace
