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

    materialize();

    return m_backend->runApp();
}

auto App::initBackend() -> void
{
    m_backend->init();
    // m_materializer = std::make_unique<Materializer>(m_backend.get());
}


auto App::materialize() -> void
{
    auto tree = ui();
    m_commands = m_materializer.build(tree);

    for (auto& cmd : m_commands)
    {
        m_backend->process(cmd);
    }

    m_commands.clear();
}


} // namespace
