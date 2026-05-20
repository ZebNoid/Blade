#pragma once

#include <any>


namespace Blade::Api {


struct RenderCommand
{
    enum class Type
    {
        Create,
        Update,
        Delete,
        Attach
    } type;


    Api::Id id;

    Api::Id parent = 0;

    Api::Text widgetType; // "Button", "Window", "Column"

    std::any props;
    std::any events;
};


} // namespace
