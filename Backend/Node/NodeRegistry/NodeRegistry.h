#pragma once

#include "Common/Types.h"
#include "Node/NativeNode/NativeNode.h"


namespace Blade::Backend {


class NodeRegistry
{
public:
    auto add(NativeNode node) -> void;

    auto get(Api::Id id) -> NativeNode*;

    auto remove(Api::Id id) -> void;

    auto clear() -> void;

    auto count() const -> size_t;

    auto collectGarbage() -> void;

private:
    std::unordered_map<Api::Id, NativeNode> m_nodes;
};


} // namespace
