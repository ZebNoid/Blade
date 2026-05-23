#include "Materializer.h"


namespace Blade {


auto Materializer::build(
    const WidgetTree& widgetTree,
    const LayoutNode& layoutTree
) -> std::vector<Api::BackendCommand>
{
    std::vector<Api::BackendCommand> commands;

    buildNode(
        widgetTree,
        layoutTree,
        commands
    );

    return commands;
}


auto Materializer::buildNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::BackendCommand>& out,
    Api::Id parent
) -> void
{
    // -------------------------------------------------
    // Generate runtime id
    // -------------------------------------------------

    const Api::Id id = nextId();

    // -------------------------------------------------
    // Native widgets only
    // -------------------------------------------------

    if (layout.isNative)
    {
        // CREATE

        out.push_back({
            .command = Api::CommandType::Create,
            .id = id,
            .parent = parent,
            .nodeType = widget.type,
            .props = widget.props,
            .events = widget.events
        });

        // ATTACH

        if (parent != Api::InvalidId)
        {
            out.push_back({
                .command = Api::CommandType::Attach,
                .id = id,
                .parent = parent
            });
        }

        // UPDATE RECT

        Api::PropertyMap props;

        if (parent == Api::InvalidId)
        {
            if (const auto it =
                    widget.props.find(Api::Props::Position);
                it != widget.props.end())
            {
                props[Api::Props::Position] = it->second;
            }
        }
        else
        {
            props[Api::Props::Position] =
                Api::Point{
                    layout.rect.x,
                    layout.rect.y
                };
        }

        props[Api::Props::Size] =
            Api::Size{
                layout.rect.width,
                layout.rect.height
            };

        out.push_back({
            .command = Api::CommandType::Update,
            .id = id,
            .props = std::move(props)
        });

        // native parent changes here
        
        parent = id;
    }

    // -------------------------------------------------
    // Children
    // -------------------------------------------------

    for (size_t i = 0;
         i < widget.children.size();
         ++i)
    {
        buildNode(
            widget.children[i],
            layout.children[i],
            out,
            parent
        );
    }
}

Api::Id Materializer::nextId()
{
    return m_nextId++;
}


} // namespace
