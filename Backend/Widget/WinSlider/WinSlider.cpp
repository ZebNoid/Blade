#include "WinSlider.h"

#include <commctrl.h>

#include "Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade::Backend {


auto WinSlider::create(
    const WidgetId id,
    const SliderProps& props,
    const int value
) -> void
{
    // TODO force redraw on resize?
    // TODO fix vertical align!
    m_id = id;
    m_props = props;
    m_value = value;

    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::GetFont("system"));

    // SendMessage(m_hwnd, TBM_SETRANGEMIN, TRUE, (LPARAM)0);
    // SendMessage(m_hwnd, TBM_SETRANGEMAX, TRUE, (LPARAM)60);
    SendMessage(m_hwnd, TBM_SETPOS, TRUE, (LPARAM)value);
}

DWORD WinSlider::style() const
{
    auto style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;

    style |= TBS_TRANSPARENTBKGND;

    style |= TBS_NOTICKS;

    style |= TBS_BOTH;

    // style |= TBS_AUTOTICKS;
    // style |= TBS_BOTTOM;
    // style |= TBS_TOP;

    // if (m_props.)
    // {
    //     style |= ;
    // }
    return style;
}

auto WinSlider::createNative(Rect rect, HWND parent) -> HWND
{
    WinWidget::createNative(rect);
    if (parent == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        0,
        TRACKBAR_CLASS, // Predefined class
        TEXT("WinSlider"), // TODO ?
        style(),
        rect.x,
        rect.y,
        rect.width,
        rect.height,
        parent,
        (HMENU)m_id, // Checkbox ID
        nullptr, // TODO m_ctx.app->hInstance,
        this
    );

    if (!m_hwnd)
    {
        std::cerr << "[Error] CheckboxNative::CreateNative " << GetLastError() << std::endl;
    }

    return m_hwnd;
}


} // namespace
