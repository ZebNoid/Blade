#include "WinRadioButton.h"

#include "Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade::Backend {


auto WinRadioButton::create(const WidgetId id, const RadioButtonProps& props, const std::string& text) -> void
{
    m_id = id;
    m_props = props;
    m_text = text;

    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::GetFont("system"));
}

DWORD WinRadioButton::style() const
{
    // TODO Start of group WS_GROUP

    // TODO BS_VCENTER?
    auto style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | BS_AUTORADIOBUTTON;

    // style |= BS_OWNERDRAW;

    if (m_props.ltr)
    {
        // Left-To-Right
        style |= (BS_RIGHTBUTTON | BS_RIGHT);
    }

    return style;
}

auto WinRadioButton::createNative(Rect rect, HWND parent) -> HWND
{
    WinWidget::createNative(rect);

    if (parent == nullptr) return nullptr;

    // TODO grouping? CheckRadioButton(hwndDlg, IDC_FIRST_RADIO, IDC_LAST_RADIO, IDC_RADIO_ONE);

    m_hwnd = CreateWindowEx(
        0,
        TEXT("BUTTON"), // Predefined class
        toNativeString(m_text).c_str(), // Label
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
