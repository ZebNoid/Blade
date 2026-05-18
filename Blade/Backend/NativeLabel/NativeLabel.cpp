#include "NativeLabel.h"

#include "Backend/Registry/ClassRegistry/ClassRegistry.h"
#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade {


auto NativeLabel::create(const WidgetContext& ctx, WidgetId id, const LabelProps& props,
                         const std::string& text) -> void
{
    m_ctx = ctx;
    m_id = id;
    m_props = props;
    m_text = text;

    ClassRegistry::Register(
        "BladeLabel",
        {
            .name = L"BladeLabel",
            .proc = WindowProc,
            .background = nullptr
        }
    );

    // TODO native size?
    // size are ignoring and recalculated in
    createNative(Rect{0, 0, 140, 32});
    m_font = ResourceRegistry::GetFont("system");
    applyFont(m_font);
}

DWORD NativeLabel::style() const
{
    auto style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
    return style;
}

DWORD NativeLabel::exStyle() const
{
    auto exStyle = 0; //WS_EX_TRANSPARENT;
    return exStyle;
}

auto NativeLabel::createNative(const Rect rect) -> HWND
{
    NativeWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        exStyle(),
        ClassRegistry::Get("BladeLabel"),
        TEXT(""),
        style(),
        rect.x, rect.y,
        rect.width, rect.height,
        m_ctx.hwnd,
        nullptr, // ID
        m_ctx.app->hInstance,
        this
    );

    // m_hwnd = CreateWindowEx(
    //     exStyle(),
    //     TEXT("STATIC"), // Classic system Label
    //     toNativeString(m_text).c_str(),
    //     // hAlign SS_LEFT || SS_CENTER ||  SS_RIGHT
    //     style() | SS_WORDELLIPSIS | SS_CENTERIMAGE | SS_CENTER,
    //     rect.x, rect.y,
    //     rect.width, rect.height,
    //     m_ctx.hwnd,
    //     nullptr, // ID
    //     m_ctx.app->hInstance,
    //     nullptr
    // );

    if (!m_hwnd)
    {
        std::cerr << "[Error] NativeLabel::CreateNative " << GetLastError() << std::endl;
    }
    return m_hwnd;
}

auto NativeLabel::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    switch (msg)
    {
    case WM_ERASEBKGND:
        return 1;

    case WM_LBUTTONDOWN:
        {
            SendMessage(
                GetParent(hwnd),
                msg,
                wParam,
                lParam
            );

            break;
        }

    // case WM_MOUSEMOVE: // WM_NCMOUSEMOVE ?
    // case WM_LBUTTONDBLCLK:
    // case WM_LBUTTONDOWN:
    // case WM_LBUTTONUP:
    // case WM_RBUTTONUP:
    // case WM_RBUTTONDBLCLK:
    // case WM_MBUTTONDOWN:
    // case WM_MBUTTONUP:
    // case WM_MBUTTONDBLCLK:
    // case WM_MOUSEWHEEL:
    // case WM_KEYDOWN:
    // case WM_KEYUP:
    // case WM_CHAR:
    //     std::cout << "!!!\n";
    //     break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            SetBkMode(hdc, TRANSPARENT);

            RECT rc;
            GetClientRect(hwnd, &rc);

            // выбрать font
            HFONT oldFont = nullptr;

            if (m_font)
            {
                oldFont = (HFONT)SelectObject(hdc, m_font);
            }

            auto text = toNativeString(m_text);

            auto style = DT_VCENTER |
                DT_SINGLELINE |
                DT_END_ELLIPSIS;

            switch (m_props.textAlign)
            {
            case TextAlign::Start:
                style |= DT_LEFT;
                break;
            case TextAlign::End:
                style |= DT_RIGHT;
                break;
            default:
                style |= DT_CENTER;
            }

            DrawTextW(
                hdc,
                text.c_str(),
                -1,
                &rc,
                style
            );

            // вернуть старый font
            if (oldFont)
            {
                SelectObject(hdc, oldFont);
            }

            EndPaint(hwnd, &ps);

            return 0;
        }

    case WM_NCHITTEST:
        return HTTRANSPARENT; // All hits pass through
    }

    return NativeWidget::handleMessage(hwnd, msg, wParam, lParam);
}


} // namespace
