#include "NativeWindow.h"

#include "Handlers/CommandHandler/CommandHandler.h"
#include "Backend/Registry/ClassRegistry/ClassRegistry.h"
#include "Backend/Registry/ResourceRegistry/ResourceRegistry.h"
#include "Context/WidgetContext.h"
#include "Debug/LayoutDebugRenderer/LayoutDebugRenderer.h"
#include "Handlers/CommandHandler/CommandHandler.h"
#include "Handlers/InputHandler/InputHandler.h"


namespace Blade {


NativeWindow::NativeWindow()
{
    m_size = {800, 600};
    // TODO move to app cycle
    ResourceRegistry::Init();
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

    // TODO set Title
    // SetWindowText(m_hwnd, toNativeString(m_props.title).c_str());
    // TODO force redraw
    // SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

auto NativeWindow::exStyle() const -> DWORD
{
    auto exStyle = 0; // WS_EX_ACCEPTFILES

    // exStyle |= WS_EX_LAYERED; // +alphe

    return exStyle;
}


auto NativeWindow::style() const -> DWORD
{
    auto style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

    // // preventing rendering artifacts when the parent redraws
    // style |= WS_CLIPCHILDREN ; // don't use without custom background

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
        return Backend::WinApi::CommandHandler::Handle(*this, wParam, lParam);

    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    // case WM_MOUSEWHEEL: // dbl click?
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_CHAR:
        return Backend::Blade::InputHandler::Handle(*this, msg, wParam, lParam);

    case WM_SETFOCUS:
    case WM_KILLFOCUS:
        break;

    case WM_ACTIVATE:
        // Detect if the user switched to a different application.
        break;

    // // case WM_LBUTTONDOWN:
    // case WM_NCLBUTTONDOWN:
    //     SetFocus(hwnd); // ? input hack? TODO
    //     break;

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
            return (LRESULT)GetStockObject(NULL_BRUSH); // transparent background ==NULL_BRUSH
            // Hack slider background?
            return (INT_PTR)GetSysColorBrush(COLOR_3DFACE);
            break;
        }

    // case WM_ERASEBKGND:
    //     return (LRESULT)TRUE; // Stop the OS from erasing the background

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

auto NativeWindow::show() -> void
{
    ShowWindow(m_hwnd, SW_SHOW);
}


} // namespace
