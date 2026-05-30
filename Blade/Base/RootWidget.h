#pragma once
#include "App/App.h"
#include "Widget.h"


namespace Blade {

template <typename TSelf>
class RootWidget : public Widget<TSelf>
{
public:
    auto mount() -> Api::Id
    {
        return App::MountRoot(*this);
    }
};


} // namespace
