#pragma once

#include <windows.h>

#include "Common/Types.h"


namespace Blade::Backend {

class ImageLoader
{
public:
    static auto LoadIcon(const Api::Text& path, int width, int height) -> HICON;
    static auto IsIcon(const Api::Text& path) -> bool;
};

} // namespace Blade::Backend
