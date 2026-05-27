#pragma once

#include <windows.h>

#include "Common/Types.h"

namespace Blade::Backend {

class WicImageLoader
{
public:
    static auto LoadIcon(const Api::Text& path, int width, int height) -> HICON;
};

} // namespace Blade::Backend
