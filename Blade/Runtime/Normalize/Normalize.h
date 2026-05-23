#pragma once

#include "EventVisitor.h"
#include "PropertyVisitor.h"
#include "Common/Property.h"


namespace Blade {


class Normalize
{
public:
    template <typename T>
    static auto Props(const T& src) -> Api::PropertyMap
    {
        PropertyVisitor visitor;
        src.visit(visitor);
        return visitor.take(); // Todo move or copy?
    }

    template <typename T>
    static auto PropsMerge(
        Api::PropertyMap& target,
        const T& src
    ) -> void
    {
        auto normalized = Props(src);
        for (auto& [key, value] : normalized)
        {
            target.insert_or_assign(key, std::move(value));
        }
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
