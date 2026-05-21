#pragma once

#include "Common/Types.h"
#include "Node/NativeNode/NativeNode.h"


namespace Blade::Backend {


class NodeRegistry
{
public:
    auto add(NativeNode node) -> void;

    auto remove(Api::Id id) -> void;

    auto get(Api::Id id) -> NativeNode*;

private:
    std::unordered_map<Api::Id, NativeNode> m_nodes;
};


} // namespace
