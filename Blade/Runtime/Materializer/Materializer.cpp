#include "Materializer.h"


namespace Blade {


auto Materializer::mount(const Api::WidgetTree& tree) -> void
{
    // TODO Materializer::mount
    // createNode(tree, nullptr);
    std::cout << "Materializer::mount" << std::endl;

    // visit(tree, {Api::RenderCommand::Type::Create}, 0);
}

auto Materializer::visit(
    const Api::WidgetTree& node,
    std::vector<Api::BackendCommand>& out,
    Api::Id parent
) -> void
{
    out.push_back({
        .command = Api::CommandType::Create,
        .id = node.id,
        .parent = parent,
        .nodeType = node.type,
        .props = node.props,
        .events = node.events
    });

    for (auto& child : node.children)
    {
        visit(child, out, node.id);
    }
}


} // namespace
