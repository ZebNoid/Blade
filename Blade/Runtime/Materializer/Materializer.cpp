#include "Materializer.h"


namespace Blade {


auto Materializer::assignIds(
    WidgetTree& widgetTree
) -> void
{
    assignNodeIds(widgetTree);
}

auto Materializer::assignNodeIds(
    WidgetTree& widget
) -> void
{
    if (widget.id == Api::InvalidId)
    {
        widget.id = nextId();
    }

    for (auto& child : widget.children)
    {
        assignNodeIds(child);
    }
}

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

auto Materializer::buildUpdates(
    const WidgetTree& widgetTree,
    const LayoutNode& layoutTree,
    bool includeRoot
) -> std::vector<Api::BackendCommand>
{
    std::vector<Api::BackendCommand> commands;

    buildUpdateNode(
        widgetTree,
        layoutTree,
        commands,
        Api::InvalidId,
        includeRoot
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

    const Api::Id id =
        widget.id != Api::InvalidId
            ? widget.id
            : nextId();

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
            .props = buildBackendProps(widget.props),
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

        auto props =
            buildRectProps(
                layout,
                widget,
                parent
            );

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

auto Materializer::buildUpdateNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::BackendCommand>& out,
    Api::Id parent,
    bool includeCurrent
) -> void
{
    Api::Id currentParent = parent;

    if (layout.isNative)
    {
        if (includeCurrent)
        {
            auto props =
                buildRectProps(
                    layout,
                    widget,
                    parent
                );

            out.push_back({
                .command = Api::CommandType::Update,
                .id = widget.id,
                .props = std::move(props)
            });
        }

        currentParent = widget.id;
    }

    for (size_t i = 0;
         i < widget.children.size();
         ++i)
    {
        buildUpdateNode(
            widget.children[i],
            layout.children[i],
            out,
            currentParent,
            true
        );
    }
}

auto Materializer::buildBackendProps(
    const Api::PropertyMap& props
) -> Api::PropertyMap
{
    Api::PropertyMap out;

    for (const auto& [key, value] : props)
    {
        switch (key)
        {
        case Api::Props::Title:
        case Api::Props::Default:
            out.insert_or_assign(key, value);
            break;

        default:
            break;
        }
    }

    return out;
}

auto Materializer::buildRectProps(
    const LayoutNode& layout,
    const WidgetTree& widget,
    Api::Id parent
) -> Api::PropertyMap
{
    Api::PropertyMap props;

    if (parent == Api::InvalidId)
    {
        auto rect = layout.rect;

        if (const auto it =
                widget.props.find(Api::Props::Position);
            it != widget.props.end())
        {
            if (const auto* position =
                    std::get_if<Api::Point>(&it->second))
            {
                rect.x = position->x;
                rect.y = position->y;
            }
        }

        props[Api::Props::Rect] = rect;
    }
    else
    {
        props[Api::Props::Rect] = layout.rect;
    }

    return props;
}

Api::Id Materializer::nextId()
{
    return m_nextId++;
}


} // namespace
