#include "WinTextField.h"

#include "Helpers/WinUtils.h"
#include "Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade::Backend {


auto WinTextField::create(
    const WidgetId id,
    const TextFieldProps& props,
    const std::wstring& text
) -> void
{
    m_id = id;
    m_props = props;
    m_text = text;

    // TODO native size?
    // size are ignoring and recalculated in
    createNative(Rect{0, 0, 140, 32});
    applyFont(ResourceRegistry::GetFont("system"));
    setPlaceholder();
}

DWORD WinTextField::style() const
{
    auto style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;

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

DWORD WinTextField::exStyle() const
{
    auto exStyle = WS_EX_CLIENTEDGE;

    if (!m_props.border)
    {
        // disable modern style border
        exStyle &= ~WS_EX_CLIENTEDGE;
    }

    return exStyle;
}

auto WinTextField::createNative(const Rect rect, HWND parent) -> HWND
{
    WinWidget::createNative(rect);
    if (parent == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        exStyle(),
        TEXT("Edit"),
        m_text.c_str(),
        style(),
        rect.x, rect.y,
        rect.width, rect.height,
        parent,
        (HMENU)m_id, // ID
        nullptr, // TODO m_ctx.app->hInstance, // <-- Must be NULL for global classes ?
        nullptr);

    if (!m_hwnd)
    {
        std::cerr << "[Error] WinTextField::CreateNative " << GetLastError() << std::endl;
    }
    return m_hwnd;
}

auto WinTextField::setPlaceholder() -> void
{
    // TODO fix Placeholder
    // LPCWSTR placeholderText = TEXT("Enter your name here...");
    // SendMessage(m_hwnd, EM_SETCUEBANNER, (WPARAM)TRUE , (LPARAM)placeholderText);

    // SendMessage(m_hwnd, EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)toNativeString(m_props.placeholder).c_str());
}

void WinTextField::setRect(const Rect& rect)
{
    WinWidget::setRect(rect);
    // SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER);
    // // TODO hack vAlign
    WinUtils::VerticalAlignCenter(m_hwnd);
}


} // namespace
