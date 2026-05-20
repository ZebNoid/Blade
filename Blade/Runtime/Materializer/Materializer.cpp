#include "Materializer.h"



namespace Blade {


auto Materializer::mount(const Api::WidgetTree& tree) -> void
{
    // createNode(tree, nullptr);
}

auto Materializer::visit(
    const Api::WidgetTree& node,
    std::vector<Api::RenderCommand>& out,
    Api::Id parent
) -> void
{
    out.push_back({
        .type = Api::RenderCommand::Type::Create,
        .id = node.id,
        .parent = parent,
        .widgetType = node.type,
        .props = node.props,
        .events = node.events
    });

    for (auto& child : node.children)
    {
        visit(child, out, node.id);
    }
}


} // namespace
