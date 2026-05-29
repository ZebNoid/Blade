#pragma once

#include <windows.h>

namespace Blade::Backend {

class FontApi
{
public:
    static auto CreateMessageFont() -> HFONT;
    static auto DefaultGuiFont() -> HFONT;
    static auto Destroy(HFONT font) -> void;
};

} // namespace Blade::Backend
