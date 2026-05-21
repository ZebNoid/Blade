#include "Materializer.h"


namespace Blade {


auto Materializer::build(
    const Api::WidgetTree& tree
) -> std::vector<Api::BackendCommand>
{
    std::vector<Api::BackendCommand> commands;

    buildNode(
        tree,
        commands
    );

    return commands;
}


auto Materializer::buildNode(
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
        .events = node.events,
    });

    if (parent != Api::InvalidId)
    {
        out.push_back({
            .command = Api::CommandType::Attach,
            .id = node.id,
            .parent = parent,
        });
    }

    for (const auto& child : node.children)
    {
        buildNode(
            child,
            out,
            node.id
        );
    }
}


} // namespace
