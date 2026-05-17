#include "NativeSlider.h"

#include <commctrl.h>

#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade {


auto NativeSlider::create(
    const WidgetContext& ctx,
    const WidgetId id,
    const SliderProps& props,
    const int value
) -> void
{
    m_ctx = ctx;
    m_id = id;
    m_props = props;
    m_value = value;

    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::GetFont("system"));

    // SendMessage(m_hwnd, TBM_SETRANGEMIN, TRUE, (LPARAM)0);
    // SendMessage(m_hwnd, TBM_SETRANGEMAX, TRUE, (LPARAM)60);
    SendMessage(m_hwnd, TBM_SETPOS, TRUE, (LPARAM)value);
}

DWORD NativeSlider::style() const
{
    auto style = WS_CHILD | WS_VISIBLE;

    style |= TBS_TRANSPARENTBKGND;

    style |= TBS_NOTICKS;
    // style |= TBS_AUTOTICKS;
    // style |= TBS_BOTTOM;
    // style |= TBS_TOP;

    // if (m_props.)
    // {
    //     style |= ;
    // }
    return style;
}

auto NativeSlider::createNative(Rect rect) -> HWND
{
    NativeWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        0,
        TRACKBAR_CLASS, // Predefined class
        TEXT("NativeSlider"), // TODO ?
        style(),
        rect.x,
        rect.y,
        rect.width,
        rect.height,
        m_ctx.hwnd,
        (HMENU)m_id, // Checkbox ID
        m_ctx.app->hInstance,
        this
    );

    if (!m_hwnd)
    {
        std::cerr << "[Error] CheckboxNative::CreateNative " << GetLastError() << std::endl;
    }

    return m_hwnd;
}

auto NativeSlider::setRect(const Rect rect) const -> void
{
    // TODO ::setRect to NativeWidget ?
    SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER);
}


} // namespace
