#pragma once
#include "App/App.h"
#include "Widget.h"


namespace Blade {

class RootWidget : public Widget
{
public:
    auto mount(App* app) -> Api::Id
    {
        return app->addToTree(*this);
    }
};


} // namespace
