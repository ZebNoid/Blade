#include "WinCheckbox.h"
#include "Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade::Backend {


auto WinCheckbox::create(const WidgetContext& ctx, const WidgetId id, const CheckboxProps& props,
                            const std::string& text) -> void
{
    m_ctx = ctx;
    m_id = id;
    m_props = props;
    m_text = text;

    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::GetFont("system"));
}

DWORD WinCheckbox::style() const
{
    // TODO BS_VCENTER?
    auto style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | BS_AUTOCHECKBOX;

    if (m_props.ltr)
    {
        // Left-To-Right
        style |= (BS_RIGHTBUTTON | BS_RIGHT);
    }

    return style;
}

auto WinCheckbox::createNative(Rect rect) -> HWND
{
    ApiWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        0,
        TEXT("BUTTON"), // Predefined class
        toNativeString(m_text).c_str(), // Label
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


} // namespace
