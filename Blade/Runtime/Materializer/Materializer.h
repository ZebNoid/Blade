#pragma once
#include <optional>

#include "Api/BackendCommand.h"


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

};


} // namespace
