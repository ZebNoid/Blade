#include "RenderApi.h"

#include <type_traits>

#include "Resource/ResourceManager/ResourceManager.h"

namespace Blade::Backend {

namespace {

auto ToRect(const Api::Rect& rect) -> RECT
{
    return {rect.x, rect.y, rect.x + rect.width, rect.y + rect.height};
}

auto Right(const Api::Rect& rect) -> int
{
    return rect.x + rect.width;
}

auto Bottom(const Api::Rect& rect) -> int
{
    return rect.y + rect.height;
}

} // namespace

auto RenderApi::Fill(HDC hdc, const Api::Rect& rect, HBRUSH brush) -> void
{
    auto nativeRect = ToRect(rect);
    FillRect(hdc, &nativeRect, brush);
}

auto RenderApi::Fill(HDC hdc, const Api::Rect& rect, Api::Color color, ResourceManager& resources, int radius) -> void
{
    if (color.a == 0) return;

    auto brush = resources.brush(color);
    auto pen = radius > 0 ? resources.pen(color) : nullptr;
    const auto previousBrush = SelectObject(hdc, brush);
    const auto previousPen = SelectObject(hdc, pen ? pen : GetStockObject(NULL_PEN));

    if (radius > 0) RoundRect(hdc, rect.x, rect.y, rect.x + rect.width + 1, rect.y + rect.height + 1, radius * 2, radius * 2);
    else Fill(hdc, rect, brush);

    SelectObject(hdc, previousPen);
    SelectObject(hdc, previousBrush);
}

auto RenderApi::Border(HDC hdc, const Api::Rect& rect, Api::Color color, ResourceManager& resources, int radius) -> void
{
    if (color.a == 0) return;

    auto pen = resources.pen(color);
    const auto previousPen = SelectObject(hdc, pen);
    const auto previousBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH));

    if (radius > 0) RoundRect(hdc, rect.x, rect.y, Right(rect), Bottom(rect), radius * 2, radius * 2);
    else Rectangle(hdc, rect.x, rect.y, Right(rect), Bottom(rect));

    SelectObject(hdc, previousBrush);
    SelectObject(hdc, previousPen);
}

auto RenderApi::Draw(HDC hdc, const Api::Rect& rect, const Api::RenderDefinition& render, ResourceManager& resources) -> void
{
    int radius = 0;

    for (const auto& op : render.ops)
    {
        std::visit(
            [hdc, &rect, &resources, &radius](const auto& value)
            {
                using T = std::decay_t<decltype(value)>;

                if constexpr (std::is_same_v<T, Api::RenderBorderRadius>)
                {
                    radius = value.radius;
                }
                else if constexpr (std::is_same_v<T, Api::RenderBackground>)
                {
                    Fill(hdc, rect, value.color, resources, radius);
                }
                else if constexpr (std::is_same_v<T, Api::RenderBorderColor>)
                {
                    Border(hdc, rect, value.color, resources, radius);
                }
            },
            op
        );
    }
}

auto RenderApi::BorderRadius(const Api::RenderDefinition& render) -> int
{
    int radius = 0;

    for (const auto& op : render.ops)
    {
        if (const auto* borderRadius = std::get_if<Api::RenderBorderRadius>(&op))
        {
            radius = borderRadius->radius;
        }
    }

    return radius;
}

auto RenderApi::TextColor(const Api::RenderDefinition& render, COLORREF fallback) -> COLORREF
{
    auto color = fallback;

    for (const auto& op : render.ops)
    {
        if (const auto* textColor = std::get_if<Api::RenderTextColor>(&op))
        {
            color = ToColorRef(textColor->color);
        }
    }

    return color;
}

auto RenderApi::Text(HDC hdc, const Api::Text& text, const Api::Rect& rect, HFONT font, COLORREF color) -> void
{
    auto nativeRect = ToRect(rect);
    const auto previousFont = font ? SelectObject(hdc, font) : nullptr;
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, color);
    DrawTextW(hdc, text.c_str(), -1, &nativeRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
    if (previousFont) SelectObject(hdc, previousFont);
}

auto RenderApi::ToColorRef(Api::Color color) -> COLORREF
{
    return RGB(color.r, color.g, color.b);
}

} // namespace Blade::Backend
