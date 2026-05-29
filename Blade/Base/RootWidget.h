#pragma once
#include "App/App.h"
#include "Widget.h"


namespace Blade {

class RootWidget : public Widget
{
public:
    auto build(App* app) -> Api::Id
    {
        return app->addToTree(*this);
    }
};


} // namespace
