#include "App.h"

#include "Runtime/LayoutEngine/Data/LayoutContext.h"
#include "Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h"
#include "Runtime/LayoutEngine/LayoutTreeBuilder/LayoutTreeBuilder.h"


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
    materialize(rootWidget.tree());
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

auto App::materialize(const WidgetTree& tree) -> void
{
    // -------------------------------------------------
    // Build layout tree
    // -------------------------------------------------

    auto layoutTree = LayoutTreeBuilder::Build(tree);

    // -------------------------------------------------
    // Measure
    // -------------------------------------------------

    LayoutContext measureCtx{
        .node = &layoutTree,
        .available = {
            1280,
            720
        }
    };

    LayoutEngine::Measure(measureCtx);

    // -------------------------------------------------
    // Arrange
    // -------------------------------------------------

    LayoutContext arrangeCtx{
        .node = &layoutTree,
        .rect = {
            3200,
            400,
            1280,
            720
        }
    };

    LayoutEngine::Arrange(arrangeCtx);

    // -------------------------------------------------
    // Build backend commands
    // -------------------------------------------------

    auto commands = m_materializer.build(
        tree,
        layoutTree
    );

    for (auto& cmd : commands)
    {
        m_backend->process(cmd);
    }
}


} // namespace
