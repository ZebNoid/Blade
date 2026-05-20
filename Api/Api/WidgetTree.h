#pragma once
#include <any>
#include <string>
#include <vector>

#include "Common/Common.h"


namespace Blade::Api {


struct WidgetTree
{
    Id id = 0;

    std::wstring type;   // "Window", "Button", "Column"

    std::any props;      // или typed variant later

    std::vector<WidgetTree> children;
};

} // namespace