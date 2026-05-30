#include "RenderRegistry.h"

namespace Blade::Backend {

auto RenderRegistry::create(const Api::RenderCommand& command) -> void
{
    m_nodes.insert_or_assign(
        command.id,
        RenderNode{
            .id = command.id,
            .root = command.root,
            .parent = command.parent,
            .order = command.order,
            .rect = command.rect,
            .render = command.render
        }
    );
}

auto RenderRegistry::update(const Api::RenderCommand& command) -> void
{
    if (auto* node = get(command.id))
    {
        node->root = command.root;
        node->parent = command.parent;
        node->order = command.order;
        node->render = command.render;
        node->rect = command.rect;
        return;
    }

    create(command);
}

auto RenderRegistry::updateRect(Api::Id id, Api::Rect rect) -> void
{
    if (auto* node = get(id)) node->rect = rect;
}

auto RenderRegistry::setState(Api::Id id, Api::WidgetState state) -> bool
{
    auto* node = get(id);
    if (!node || node->state == state) return false;

    node->state = state;
    return true;
}

auto RenderRegistry::remove(Api::Id id) -> void
{
    m_nodes.erase(id);
}

auto RenderRegistry::clear() -> void
{
    m_nodes.clear();
}

auto RenderRegistry::get(Api::Id id) -> RenderNode*
{
    const auto it = m_nodes.find(id);
    return it == m_nodes.end() ? nullptr : &it->second;
}

auto RenderRegistry::count() const -> size_t
{
    return m_nodes.size();
}

} // namespace Blade::Backend
