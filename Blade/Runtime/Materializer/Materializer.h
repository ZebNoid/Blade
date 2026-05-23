#pragma once

#include "Api/BackendCommand.h"
#include "Base/WidgetTree.h"


namespace Blade {


class Materializer
{
public:
    auto build(
        const WidgetTree& tree
    ) -> std::vector<Api::BackendCommand>;

private:
    auto buildNode(
        const WidgetTree& node,
        std::vector<Api::BackendCommand>& out,
        Api::Id parent = Api::InvalidId
    ) -> void;

private:
    Api::Id nextId();

private:
    // TODO persistent widget IDs (assigned at construction)
    Api::Id m_nextId = 1;
};


} // namespace
