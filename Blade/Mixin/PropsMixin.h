#pragma once

#include <utility>


namespace Blade {


template <typename Derived>
class PropsMixin
{
public:
    template <typename T>
    auto set(T prop) -> Derived&
    {
        static_cast<Derived*>(this)->applyProp(std::move(prop));
        return static_cast<Derived&>(*this);
    }
};


} // namespace
