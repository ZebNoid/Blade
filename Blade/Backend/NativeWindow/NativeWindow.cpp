#include "NativeWindow.h"

#include "Backend/Registry/ClassRegistry/ClassRegistry.h"
#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"
#include "Context/WidgetContext.h"
#include "Core/Encoding.h"
#include "Debug/LayoutDebugRenderer/LayoutDebugRenderer.h"


namespace Blade {


NativeWindow::NativeWindow()
{
    m_size = {800, 600};
    // TODO move to app cycle
    ResourceRegistry::init();
}

auto NativeWindow::create(const WidgetContext& ctx, Window* owner, const WindowProps& props) -> void
{
    m_ctx = ctx;
    // TODO id
    m_props = props;
    m_owner = owner;

    ClassRegistry::Init(ctx.app->hInstance);

    ClassRegistry::Register(
        "NativeWindow",
        {
            .name = L"NativeWindowClass",
            .proc = WindowProc,
            // .background = (HBRUSH)COLOR_HIGHLIGHTTEXT,
            // TODO set window icon
            .icon = LoadIcon(ctx.app->hInstance, MAKEINTRESOURCE(101)),
            // .icon = LoadIcon(ctx.app->hInstance, MAKEINTRESOURCE(IDI_APP_ICON)),
        }
    );

    createNative({});
}

auto NativeWindow::exStyle() const -> DWORD
{
    auto exStyle = 0; //  WS_EX_LAYERED | WS_EX_ACCEPTFILES
    return exStyle;
}


auto NativeWindow::style() const -> DWORD
{
    auto style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

    if (!m_props.resizable)
    {
        style &= ~WS_THICKFRAME;
    }

    if (!m_props.maximizable)
    {
        style &= ~WS_MAXIMIZEBOX;
    }

    if (!m_props.minimizable)
    {
        style &= ~WS_MINIMIZEBOX;
    }

    return style;
}

auto NativeWindow::createNative(const Rect rect) -> HWND
{
    m_hwnd = CreateWindowEx(
        exStyle(),
        ClassRegistry::Get("NativeWindow"),
        toNativeString(m_props.title).c_str(),
        style(),
        // TODO remember size / position
        // TODO center
        m_props.position.x, m_props.position.y,
        m_props.size.width, m_props.size.height,
        // for root window it always m_ctx.hwnd = nullptr
        // m_ctx.hwnd != nullptr ? m_ctx.hwnd : HWND_DESKTOP,
        m_ctx.hwnd,
        nullptr,
        m_ctx.app->hInstance,
        this);

    if (!m_hwnd)
    {
        std::cerr << "[Error] NativeWindow::CreateNative " << GetLastError() << std::endl;
    }

    // SetLayeredWindowAttributes(m_hwnd, 0, (255 * 70) / 100, LWA_ALPHA);
    // SetLayeredWindowAttributes(m_hwnd, 0, 128, LWA_ALPHA);
    // SetLayeredWindowAttributes(m_hwnd, RGB(255, 0, 0), 128, LWA_COLORKEY);

    return m_hwnd;
}

auto NativeWindow::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    switch (msg)
    {
    case WM_CREATE:
        {
            // CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            // int width = pCreate->cx;
            // int height = pCreate->cy;
            // int x = pCreate->x;
            // int y = pCreate->y;
            return 0;
        }

    case WM_COMMAND:
        return handleCommandMessage(hwnd, msg, wParam, lParam);

    case WM_ACTIVATE:
        // Detect if the user switched to a different application.
        break;

    // case WM_LBUTTONDOWN:
    case WM_NCLBUTTONDOWN:
        SetFocus(hwnd);
        break;

    case WM_NCHITTEST:
        {
            LRESULT hit = DefWindowProc(hwnd, msg, wParam, lParam);
            // If the click is in the client area, tell Windows it's the caption
            if (hit == HTCLIENT)
            {
                return HTCAPTION;
            }
            return hit;
        }

    case WM_SIZE:
        {
            m_size.width = LOWORD(lParam);
            m_size.height = HIWORD(lParam);

            m_owner->onResize(m_size);
            return 0;
        }

    // case WM_NCMOUSEMOVE:
    // // case WM_MOUSEMOVE:
    //     {
    //         int x = GET_X_LPARAM(lParam);
    //         int y = GET_Y_LPARAM(lParam);
    //     }
    //     break;

    // case WM_CTLCOLORBTN:
    // case WM_CTLCOLOREDIT:
    case WM_CTLCOLORSTATIC:
        {
            // "STATIC" label background transparency
            // auto childHwnd = (HWND)lParam;
            const auto hdc = (HDC)wParam;
            SetBkMode(hdc, TRANSPARENT);
            // transparent background
            return (LRESULT)GetStockObject(NULL_BRUSH); // NULL_BRUSH
        }

    case WM_PAINT:
        {
// #ifdef BLADE_DEBUG_LAYOUT
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            LayoutDebugRenderer::Render(hdc, *m_owner->m_root);
            EndPaint(hwnd, &ps);
// #endif
            return 0;
        }
        break;

    // case WM_SETCURSOR:
    //     // Check if the cursor is in the client area (not the title bar)
    //     if (LOWORD(lParam) == HTCLIENT) {
    //         // Load a standard system cursor (e.g., Crosshair)
    //         HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
    //         SetCursor(hCursor);
    //         return TRUE; // Tell Windows we handled it
    //     }
    //     break;

    case WM_CLOSE:
        {
            // TODO check multiple windows
            DestroyWindow(hwnd);
            return 0;
        }

    case WM_DESTROY:
        m_owner->onDestroy();
        return 0;

    case WM_NCDESTROY:
        {
            SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
            m_hwnd = nullptr;
            return 0;
        }
    }

    return NativeWidget::handleMessage(hwnd, msg, wParam, lParam);
}

inline auto NativeWindow::handleCommandMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    const int id = LOWORD(wParam);
    const int event = HIWORD(wParam);
    const auto currentHwnd = (HWND)lParam;

    switch (event)
    {
    case EN_CHANGE:
        {
            const int len = GetWindowTextLength(currentHwnd);
            if (len <= 0) break;

            std::wstring buffer(len + 1, L'\0');
            GetWindowText(currentHwnd, &buffer[0], len + 1);
            // GetWindowText(hEdit, buffer.data(), len + 1);
            m_owner->dispatchCommand(id, WidgetEvent::Change, Utf16ToUtf8(buffer));
            VerticalAlignCenter(currentHwnd); // TODO dev
        }
        break;

    case EN_SETFOCUS:
        m_owner->dispatchCommand(id, WidgetEvent::Focus, true);
        break;

    case EN_KILLFOCUS:
        m_owner->dispatchCommand(id, WidgetEvent::Focus, false);
        break;

    case BN_CLICKED:
        {
            LONG_PTR style = GetWindowLongPtr(currentHwnd, GWL_STYLE);
            LONG_PTR type = style & BS_TYPEMASK;

            if (type == BS_AUTOCHECKBOX)
            {
                LRESULT state = SendMessage(currentHwnd, BM_GETCHECK, 0, 0);
                auto isChecked = state == BST_CHECKED;
                m_owner->dispatchCommand(id, WidgetEvent::Change, isChecked);
            }
            else if (type == BS_AUTORADIOBUTTON)
            {
                LRESULT state = SendMessage(currentHwnd, BM_GETCHECK, 0, 0);
                auto isChecked = state == BST_CHECKED;
                m_owner->dispatchCommand(id, WidgetEvent::Change, isChecked);
            }
            else
            {
                m_owner->dispatchCommand(id, WidgetEvent::Click);
            }
        }
        break;

    default: ;
    }
    return 0;
}

auto NativeWindow::setRect(Rect rect) -> void
{
    // MoveWindow(m_hwnd, rect.x, rect.y, rect.width, rect.height, TRUE);
    // SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height,  SWP_NONE);
}

// auto NativeWindow::setTitle(const std::string& title) -> void
// {
//     SetWindowText(m_hwnd, toNativeString(m_props.title).c_str());
// }

auto NativeWindow::setSize(const Size size) -> void
{
    m_size = size;
    SetWindowPos(m_hwnd, nullptr, 0, 0, size.width, size.height, SWP_NOMOVE);
}

auto NativeWindow::show() -> void
{
    ShowWindow(m_hwnd, SW_SHOW);
}

// TODO force redraw
// SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

} // namespace
