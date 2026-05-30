#pragma once

#include <windows.h>

#include "Geometry/Rect.h"
#include "Common/Types.h"
#include "Render/RenderOp.h"

namespace Blade::Backend {

class ResourceManager;

class RenderApi
{
public:
    static auto Fill(HDC hdc, const Api::Rect& rect, HBRUSH brush) -> void;
    static auto Fill(HDC hdc, const Api::Rect& rect, Api::Color color, ResourceManager& resources, int radius = 0) -> void;
    static auto Border(HDC hdc, const Api::Rect& rect, Api::Color color, ResourceManager& resources, int radius = 0) -> void;
    static auto Draw(HDC hdc, const Api::Rect& rect, const Api::RenderDefinition& render, ResourceManager& resources) -> void;
    static auto BorderRadius(const Api::RenderDefinition& render) -> int;
    static auto TextColor(const Api::RenderDefinition& render, COLORREF fallback) -> COLORREF;
    static auto Text(HDC hdc, const Api::Text& text, const Api::Rect& rect, HFONT font, COLORREF color) -> void;
    static auto ToColorRef(Api::Color color) -> COLORREF;
};

} // namespace Blade::Backend
