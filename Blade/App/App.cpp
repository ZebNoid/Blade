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
    auto tree = rootWidget.tree();

    m_materializer.assignIds(tree);

    const auto rootId = tree.id;

    materialize(tree);

    m_roots.insert_or_assign(
        rootId,
        std::move(tree)
    );
}

auto App::initBackend() -> int
{
    if (!m_backend)
    {
        std::cerr << "No Backend set" << std::endl;
        return -1;
    }
    m_backend->init();
    m_backend->setResizeHandler(
        [this](Api::Id rootId, const Api::Size& size)
        {
            onNativeResize(rootId, size);
        }
    );
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

    const auto rootSize = layoutTree.layout.size;

    LayoutContext arrangeCtx{
        .node = &layoutTree,
        .rect = {
            0,
            0,
            rootSize.width,
            rootSize.height
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

auto App::updateLayout(
    const WidgetTree& tree,
    const Api::Size& size
) -> void
{
    auto layoutTree = LayoutTreeBuilder::Build(tree);
    layoutTree.layout.size = size;

    LayoutContext measureCtx{
        .node = &layoutTree,
        .available = size
    };

    LayoutEngine::Measure(measureCtx);

    LayoutContext arrangeCtx{
        .node = &layoutTree,
        .rect = {
            0,
            0,
            size.width,
            size.height
        }
    };

    LayoutEngine::Arrange(arrangeCtx);

    auto commands = m_materializer.buildUpdates(
        tree,
        layoutTree,
        false
    );

    for (auto& cmd : commands)
    {
        m_backend->process(cmd);
    }
}

auto App::onNativeResize(
    Api::Id rootId,
    const Api::Size& size
) -> void
{
    const auto it = m_roots.find(rootId);

    if (it == m_roots.end())
    {
        return;
    }

    updateLayout(
        it->second,
        size
    );
}


} // namespace
