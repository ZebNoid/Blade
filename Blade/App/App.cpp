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
    buildUi();

    return m_backend->runApp();
}

auto App::initBackend() -> void
{
    m_backend->init();
    m_materializer = std::make_unique<Materializer>(m_backend.get());
}

auto App::buildUi() -> void
{
    // ui();
    m_materializer->mount(ui());
}


} // namespace
