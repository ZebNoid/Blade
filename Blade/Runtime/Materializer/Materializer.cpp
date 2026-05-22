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
    const Api::Id id = nextId();

    out.push_back({
        .command = Api::CommandType::Create,
        .id = id,
        .parent = parent,
        .nodeType = node.type,
        .props = node.props,
        .events = node.events,
    });

    if (parent != Api::InvalidId)
    {
        out.push_back({
            .command = Api::CommandType::Attach,
            .id = id,
            .parent = parent,
        });
    }

    for (const auto& child : node.children)
    {
        buildNode(child, out, id);
    }
}

Api::Id Materializer::nextId()
{
    return m_nextId++;
}


} // namespace
