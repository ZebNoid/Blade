#include "RenderApi.h"

namespace Blade::Backend {

namespace {

auto ToRect(const Api::Rect& rect) -> RECT
{
    return {rect.x, rect.y, rect.x + rect.width, rect.y + rect.height};
}

} // namespace

auto RenderApi::Fill(HDC hdc, const Api::Rect& rect, HBRUSH brush) -> void
{
    auto nativeRect = ToRect(rect);
    FillRect(hdc, &nativeRect, brush);
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

} // namespace Blade::Backend
