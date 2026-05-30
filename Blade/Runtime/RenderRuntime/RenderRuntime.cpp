#include "RenderRuntime.h"

#include "Runtime/Render/RenderDefinitionBuilder.h"

namespace Blade {

namespace {

auto SameRect(const LayoutNode* previousLayout, const LayoutNode& layout) -> bool
{
    if (!previousLayout) return false;

    const auto& a = previousLayout->rect;
    const auto& b = layout.rect;
    return a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height;
}

} // namespace

RenderRuntime::RenderRuntime(Api::ApiBackend* backend)
    : m_backend(backend)
{
}

auto RenderRuntime::create(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> void
{
    std::vector<Api::RenderCommand> commands;
    int order = 0;
    createNode(widgetTree, layoutTree, commands, widgetTree.id, Api::InvalidId, order);
    send(commands);
}

auto RenderRuntime::updateChanged(const WidgetTree& widgetTree, const LayoutNode& previousLayout, const LayoutNode& layoutTree) -> void
{
    std::vector<Api::RenderCommand> commands;
    updateChangedNode(widgetTree, &previousLayout, layoutTree, commands);
    send(commands);
}

auto RenderRuntime::remove(const WidgetTree& widgetTree) -> void
{
    std::vector<Api::RenderCommand> commands;
    removeNode(widgetTree, commands);
    send(commands);
}

auto RenderRuntime::createNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::RenderCommand>& out,
    Api::Id root,
    Api::Id parent,
    int& order
) -> void
{
    const auto render = RenderDefinitionBuilder::Build(widget.modifier);
    const auto hasRender = !render.empty();

    if (hasRender)
    {
        out.push_back({
            .command = Api::RenderCommandType::Create,
            .id = widget.id,
            .root = root,
            .parent = parent,
            .order = order++,
            .rect = layout.rect,
            .render = render
        });

        parent = widget.id;
    }

    for (size_t i = 0; i < widget.children.size(); ++i)
    {
        createNode(widget.children[i], layout.children[i], out, root, parent, order);
    }
}

auto RenderRuntime::updateChangedNode(
    const WidgetTree& widget,
    const LayoutNode* previousLayout,
    const LayoutNode& layout,
    std::vector<Api::RenderCommand>& out
) -> void
{
    const auto render = RenderDefinitionBuilder::Build(widget.modifier);
    if (!render.empty() && !SameRect(previousLayout, layout))
    {
        out.push_back({
            .command = Api::RenderCommandType::UpdateRect,
            .id = widget.id,
            .rect = layout.rect
        });
    }

    for (size_t i = 0; i < widget.children.size(); ++i)
    {
        const auto* previousChild = previousLayout && i < previousLayout->children.size() ? &previousLayout->children[i] : nullptr;
        updateChangedNode(widget.children[i], previousChild, layout.children[i], out);
    }
}

auto RenderRuntime::removeNode(const WidgetTree& widget, std::vector<Api::RenderCommand>& out) -> void
{
    for (const auto& child : widget.children)
    {
        removeNode(child, out);
    }

    for (const auto& overlay : widget.overlays)
    {
        removeNode(overlay, out);
    }

    if (!RenderDefinitionBuilder::Build(widget.modifier).empty())
    {
        out.push_back({
            .command = Api::RenderCommandType::Remove,
            .id = widget.id
        });
    }
}

auto RenderRuntime::send(const std::vector<Api::RenderCommand>& commands) -> void
{
    if (!m_backend) return;

    for (const auto& command : commands)
    {
        m_backend->process(command);
    }
}

} // namespace Blade
