#include "NativeRadioButton.h"

#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade {


auto NativeRadioButton::create(const WidgetContext& ctx, const WidgetId id, const std::string& text) -> void
{
    m_ctx = ctx;
    m_id = id;
    m_text = text;

    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::get_font("system"));
}

auto NativeRadioButton::createNative(Rect rect) -> HWND
{
    NativeWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    // TODO grouping? CheckRadioButton(hwndDlg, IDC_FIRST_RADIO, IDC_LAST_RADIO, IDC_RADIO_ONE);

    m_hwnd = CreateWindowEx(
        0,
        L"BUTTON", // Predefined class
        toNativeString(m_text).c_str(), // Label
        // TODO Start of group WS_GROUP
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
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

auto NativeRadioButton::setRect(const Rect rect) const -> void
{
    // TODO ::setRect to NativeWidget ?
    SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER);
}


} // namespace
