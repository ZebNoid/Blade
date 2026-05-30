#pragma once
#include "App/App.h"
#include "Widget.h"


namespace Blade {

class RootWidget : public Widget
{
public:
    auto mount() -> Api::Id
    {
        return App::MountRoot(*this);
    }
};


} // namespace
