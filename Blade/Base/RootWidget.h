#pragma once
#include "App/App.h"
#include "Widget.h"


namespace Blade {

class RootWidget : public Widget
{
public:
    auto build(App* app) -> void
    {
        app->addToTree(*this);
    }
};


} // namespace
