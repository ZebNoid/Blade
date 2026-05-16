#include "NativeCheckbox.h"

#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade {


auto NativeCheckbox::create(const WidgetContext& ctx, const WidgetId id, const CheckboxProps& props,
                            const std::string& text) -> void
{
    m_ctx = ctx;
    m_id = id;
    m_props = props;
    m_text = text;

    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::get_font("system"));
}

DWORD NativeCheckbox::style() const
{
    auto style = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX;

    if (m_props.ltr)
    {
        // Left-To-Right
        style |= (BS_RIGHTBUTTON | BS_RIGHT);
    }

    return style;
}

auto NativeCheckbox::createNative(Rect rect) -> HWND
{
    NativeWidget::createNative(rect);
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

auto NativeCheckbox::setRect(const Rect rect) const -> void
{
    // TODO ::setRect to NativeWidget ?
    SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER);
}


} // namespace
