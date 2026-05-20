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
    buildUi();

    return m_backend->runApp();
}

auto App::initBackend() -> void
{
    m_backend->init();
}

auto App::buildUi() -> void
{

}


} // namespace
