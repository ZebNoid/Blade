#pragma once

#include "Common/Common.h"

namespace Blade {


struct WindowProps
{
    Api::Text title = L"Blade"; // TODO later
    Api::Size size{800, 600};
    Api::Point position{-1 , -1 };

};


} // namespace
