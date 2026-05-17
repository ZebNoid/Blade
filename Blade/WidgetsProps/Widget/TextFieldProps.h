#pragma once

#include "WidgetsProps/LayoutProps/LayoutProps.h"
#include "WidgetsProps/Common/TextAlign.h"


namespace Blade {


struct TextFieldProps
{
    LayoutProps layout;
    // bit mask?
    TextAlign textAlign = TextAlign::Start;
    std::string placeholder = "";
    int maxLines = 0;
    bool readOnly = false;
    bool autoScroll = true;
    bool border = true;

    // TODO
    // Uppercase
    // Lowercase
    // Password
    // Number
};


} // namespace
