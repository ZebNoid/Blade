#pragma once

#include <unordered_map>

#include "Render/RenderCommand.h"
#include "Render/RenderNode/RenderNode.h"

namespace Blade::Backend {

class RenderRegistry
{
public:
    auto create(const Api::RenderCommand& command) -> void;
    auto update(const Api::RenderCommand& command) -> void;
    auto updateRect(Api::Id id, Api::Rect rect) -> void;
    auto remove(Api::Id id) -> void;
    auto clear() -> void;
    auto get(Api::Id id) -> RenderNode*;
    auto count() const -> size_t;

private:
    std::unordered_map<Api::Id, RenderNode> m_nodes;
};

} // namespace Blade::Backend
