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
        return visitor.map(); // Todo Move?
    }


    template <typename T>
    static auto Events(const T& src) -> Api::EventMap
    {
        EventVisitor visitor;
        src.visit(visitor);
        return visitor.map(); // Todo Move?
    }
};

} // namespace
