#pragma once

#include <windows.h>

#include "Common/Rect.h"
#include "Common/Types.h"

namespace Blade::Backend {

class RenderApi
{
public:
    static auto Fill(HDC hdc, const Api::Rect& rect, HBRUSH brush) -> void;
    static auto Text(HDC hdc, const Api::Text& text, const Api::Rect& rect, HFONT font, COLORREF color) -> void;
};

} // namespace Blade::Backend
