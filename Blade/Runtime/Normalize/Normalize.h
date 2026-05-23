#pragma once

#include "EventVisitor.h"
#include "PropertyVisitor.h"
#include "Common/Property.h"
#include "Base/WidgetTree.h"


namespace Blade {


class Normalize
{
public:
    template <typename T>
    static auto Props(const T& src) -> NormalizedProps
    {
        PropertyVisitor visitor;
        src.visit(visitor);
        return visitor.take();
    }

    template <typename T>
    static auto PropsMerge(
        WidgetTree& target,
        const T& src
    ) -> void
    {
        auto normalized = Props(src);
        target.backend.merge(std::move(normalized.backend));
        normalized.applyTo(target.layout);
    }

    template <typename T>
    static auto Events(const T& src) -> Api::EventMap
    {
        EventVisitor visitor;
        src.visit(visitor);
        return visitor.take(); // Todo move or copy?
    }
};

} // namespace
