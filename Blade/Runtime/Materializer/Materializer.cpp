#include "Materializer.h"

#include "Runtime/Materializer/MaterializerCommands/MaterializerCommands.h"

namespace Blade {

namespace {

template <typename T>
auto Get(const Api::PropertyMap& map, Api::Props prop) -> const T*
{
    const auto it = map.find(prop);
    return it == map.end() ? nullptr : std::get_if<T>(&it->second);
}

auto Trigger(const WidgetTree& menu) -> Api::MenuTrigger
{
    const auto* trigger = Get<Api::MenuTrigger>(menu.backend.create, Api::Props::MenuTrigger);
    return trigger ? *trigger : Api::MenuTrigger::RightClick;
}

auto Title(const WidgetTree& item) -> Api::Text
{
    const auto* title = Get<Api::Text>(item.backend.create, Api::Props::Title);
    return title ? *title : L"";
}

auto BuildMenus(const std::vector<WidgetTree>* overlays) -> Api::ContextMenus
{
    Api::ContextMenus result;
    if (!overlays) return result;

    for (const auto& menu : *overlays)
    {
        Api::MenuData data{ .trigger = Trigger(menu) };

        for (const auto& item : menu.children)
        {
            data.items.push_back({
                .id = item.id,
                .title = Title(item)
            });
        }

        result.push_back(std::move(data));
    }

    return result;
}

auto IsContextArea(const WidgetTree& widget) -> bool
{
    return widget.type == L"ContextArea";
}

} // namespace

auto Materializer::create(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::ElementCommand>
{
    std::vector<Api::ElementCommand> commands;

    createNode(widgetTree, layoutTree, commands);

    return commands;
}

auto Materializer::update(const WidgetTree& widgetTree, const LayoutNode& layoutTree, bool includeRoot) -> std::vector<Api::ElementCommand>
{
    std::vector<Api::ElementCommand> commands;

    updateNode(widgetTree, layoutTree, commands, Api::InvalidId, includeRoot);

    return commands;
}


auto Materializer::createNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::ElementCommand>& out,
    Api::Id parent,
    const std::vector<WidgetTree>* contextMenus
) -> void
{
    if (layout.layoutType == LayoutType::None)
    {
        out.push_back(MaterializerCommands::Create(widget, parent, BuildMenus(contextMenus)));

        if (parent != Api::InvalidId)
        {
            out.push_back(MaterializerCommands::Attach(widget, parent));
        }

        out.push_back(MaterializerCommands::Update(layout, widget, parent));

        if (parent == Api::InvalidId)
        {
            out.push_back(MaterializerCommands::Visible(widget));
        }

        parent = widget.id;
    }

    const auto* childContextMenus = IsContextArea(widget) ? &widget.overlays : nullptr;

    for (size_t i = 0; i < widget.children.size(); ++i)
    {
        createNode(widget.children[i], layout.children[i], out, parent, childContextMenus);
    }
}

auto Materializer::updateNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::ElementCommand>& out,
    Api::Id parent,
    bool includeCurrent
) -> void
{
    Api::Id currentParent = parent;

    if (layout.layoutType == LayoutType::None)
    {
        if (includeCurrent)
        {
            out.push_back(MaterializerCommands::Update(layout, widget, parent));
        }

        currentParent = widget.id;
    }

    for (size_t i = 0; i < widget.children.size(); ++i)
    {
        updateNode(widget.children[i], layout.children[i], out, currentParent, true);
    }
}

} // namespace
