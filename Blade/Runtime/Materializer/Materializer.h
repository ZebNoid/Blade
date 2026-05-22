#pragma once

#include "Api/BackendCommand.h"
#include "Api/WidgetTree.h"


namespace Blade {


class Materializer
{
public:
    auto build(
        const Api::WidgetTree& tree
    ) -> std::vector<Api::BackendCommand>;

private:
    auto buildNode(
        const Api::WidgetTree& node,
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
