#pragma once

#include <windows.h>

#include "Geometry/Rect.h"
#include "Render/RenderOp.h"

namespace Blade::Backend {

class ResourceManager;

class GdiPlusRenderApi
{
public:
    static auto Draw(HDC hdc, const Api::Rect& rect, const Api::RenderDefinition& render, ResourceManager& resources) -> void;
    static auto Fill(HDC hdc, const Api::Rect& rect, Api::Color color, ResourceManager& resources, int radius = 0) -> void;
    static auto Border(HDC hdc, const Api::Rect& rect, Api::Color color, ResourceManager& resources, int radius = 0) -> void;
};

} // namespace Blade::Backend
