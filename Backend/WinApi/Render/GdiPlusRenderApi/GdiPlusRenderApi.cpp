#include "GdiPlusRenderApi.h"

#include <algorithm>
#include <type_traits>

#include <gdiplus.h>

namespace Blade::Backend {

namespace {

auto ToColor(Api::Color color) -> Gdiplus::Color
{
    return {
        static_cast<BYTE>(std::clamp(color.a, 0, 255)),
        static_cast<BYTE>(std::clamp(color.r, 0, 255)),
        static_cast<BYTE>(std::clamp(color.g, 0, 255)),
        static_cast<BYTE>(std::clamp(color.b, 0, 255))
    };
}

auto AddRoundRect(Gdiplus::GraphicsPath& path, const Api::Rect& rect, int radius) -> void
{
    const auto diameter = radius < 1 ? 1 : radius * 2;
    const auto right = rect.x + rect.width - 1;
    const auto bottom = rect.y + rect.height - 1;

    path.AddArc(rect.x, rect.y, diameter, diameter, 180, 90);
    path.AddArc(right - diameter, rect.y, diameter, diameter, 270, 90);
    path.AddArc(right - diameter, bottom - diameter, diameter, diameter, 0, 90);
    path.AddArc(rect.x, bottom - diameter, diameter, diameter, 90, 90);
    path.CloseFigure();
}

auto Setup(Gdiplus::Graphics& graphics) -> void
{
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
    graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
}

} // namespace

auto GdiPlusRenderApi::Draw(HDC hdc, const Api::Rect& rect, const Api::RenderDefinition& render) -> void
{
    int radius = 0;

    for (const auto& op : render.ops)
    {
        std::visit(
            [hdc, &rect, &radius](const auto& value)
            {
                using T = std::decay_t<decltype(value)>;

                if constexpr (std::is_same_v<T, Api::RenderBorderRadius>)
                {
                    radius = value.radius;
                }
                else if constexpr (std::is_same_v<T, Api::RenderBackground>)
                {
                    Fill(hdc, rect, value.color, radius);
                }
                else if constexpr (std::is_same_v<T, Api::RenderBorderColor>)
                {
                    Border(hdc, rect, value.color, radius);
                }
            },
            op
        );
    }
}

auto GdiPlusRenderApi::Fill(HDC hdc, const Api::Rect& rect, Api::Color color, int radius) -> void
{
    if (color.a == 0 || rect.width <= 0 || rect.height <= 0) return;

    auto graphics = Gdiplus::Graphics(hdc);
    Setup(graphics);
    auto brush = Gdiplus::SolidBrush(ToColor(color));

    if (radius <= 0)
    {
        graphics.FillRectangle(&brush, rect.x, rect.y, rect.width, rect.height);
        return;
    }

    auto path = Gdiplus::GraphicsPath();
    AddRoundRect(path, rect, radius);
    graphics.FillPath(&brush, &path);
}

auto GdiPlusRenderApi::Border(HDC hdc, const Api::Rect& rect, Api::Color color, int radius) -> void
{
    if (color.a == 0 || rect.width <= 0 || rect.height <= 0) return;

    auto graphics = Gdiplus::Graphics(hdc);
    Setup(graphics);
    auto pen = Gdiplus::Pen(ToColor(color), 1.0F);

    if (radius <= 0)
    {
        graphics.DrawRectangle(&pen, rect.x, rect.y, rect.width - 1, rect.height - 1);
        return;
    }

    auto path = Gdiplus::GraphicsPath();
    AddRoundRect(path, rect, radius);
    graphics.DrawPath(&pen, &path);
}

} // namespace Blade::Backend
