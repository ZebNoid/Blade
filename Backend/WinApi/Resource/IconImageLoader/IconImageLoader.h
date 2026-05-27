#pragma once

#include <windows.h>

#include "Common/Types.h"

namespace Blade::Backend {

class IconImageLoader
{
public:
    static auto Load(const Api::Text& path, int width, int height) -> HICON;
};

} // namespace Blade::Backend
