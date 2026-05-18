#pragma once

#include <string>
#include <windows.h>

#include "Backend/NativeRender/NativeRenderContext.h"
#include "Core/Rect.h"


namespace Blade::Backend {
class NativeRender
{
public:
    static auto FillRect(
        NativeRenderContext& ctx,
        Rect rect,
        Color color
    ) -> void;

    static auto DrawRect(
        NativeRenderContext& ctx,
        Rect rect,
        Color color,
        int thickness = 1
    ) -> void;

    static auto DrawLine(
        NativeRenderContext& ctx,
        int x1,
        int y1,
        int x2,
        int y2,
        Color color,
        int thickness = 1
    ) -> void;

    static auto DrawText(
        NativeRenderContext& ctx,
        Rect rect,
        const std::wstring& text,
        Color color
    ) -> void;
};

} // namespace
