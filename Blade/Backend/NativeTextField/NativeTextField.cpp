#include "NativeTextField.h"

#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade {


auto NativeTextField::create(const WidgetContext& ctx, const WidgetId id, const TextFieldProps& props,
                             const std::string& text) -> void
{
    m_ctx = ctx;
    m_id = id;
    m_props = props;
    m_text = text;

    // TODO native size?
    // size are ignoring and recalculated in
    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::GetFont("system"));
    setPlaceholder();
}

DWORD NativeTextField::style() const
{
    auto style = WS_CHILD | WS_VISIBLE;

    // if (m_props.border)
    // {
    //     // plain border, no modern style
    //     style |= WS_BORDER;
    // }

    if (m_props.maxLines != 1)
    {
        style |= ES_MULTILINE;
    }

    if (m_props.readOnly)
    {
        style |= ES_READONLY;
    }

    if (m_props.autoScroll)
    {
        style |= ES_AUTOVSCROLL;
        style |= ES_AUTOHSCROLL;
    }

    // TODO
    // ES_UPPERCASE
    // ES_LOWERCASE
    // ES_PASSWORD
    // ES_NUMBER

    switch (m_props.textAlign)
    {
    case TextAlign::End:
        style |= ES_RIGHT;
        break;
    case TextAlign::Center:
        style |= ES_CENTER;
        break;
    default:
        style |= ES_LEFT;
    }

    return style;
}

DWORD NativeTextField::exStyle() const
{
    auto exStyle = WS_EX_CLIENTEDGE;

    if (!m_props.border)
    {
        // disable modern style border
        exStyle &= ~WS_EX_CLIENTEDGE;
    }

    return exStyle;
}

auto NativeTextField::createNative(const Rect rect) -> HWND
{
    NativeWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        exStyle(),
        TEXT("Edit"),
        toNativeString(m_text).c_str(),
        style(),
        rect.x, rect.y,
        rect.width, rect.height,
        m_ctx.hwnd,
        (HMENU)m_id, // ID
        m_ctx.app->hInstance, // <-- Must be NULL for global classes ?
        nullptr);

    if (!m_hwnd)
    {
        std::cerr << "[Error] NativeTextField::CreateNative " << GetLastError() << std::endl;
    }
    return m_hwnd;
}

auto NativeTextField::setPlaceholder() -> void
{
    // TODO fix Placeholder
    // LPCWSTR placeholderText = TEXT("Enter your name here...");
    // SendMessage(m_hwnd, EM_SETCUEBANNER, (WPARAM)TRUE , (LPARAM)placeholderText);

    // SendMessage(m_hwnd, EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)toNativeString(m_props.placeholder).c_str());
}


auto NativeTextField::setRect(const Rect rect) -> void
{
    NativeWidget::setRect(rect);
    // SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER);
    // // TODO hack vAlign
    VerticalAlignCenter(m_hwnd);
}


} // namespace
