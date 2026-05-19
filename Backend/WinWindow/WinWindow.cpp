#include "Handlers/CommandHandler/CommandHandler.h"
#include "Handlers/InputHandler/InputHandler.h"
#include "Handlers/PaintHandler/PaintHandler.h"
#include "Handlers/WindowHandler/WindowHandler.h"
#include "Helpers/Helpers.h"
#include "Registry/ClassRegistry/ClassRegistry.h"
#include "Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade::Backend {

#define CUSTOM_CLASS_KEY "WinWindowKey"
#define NATIVE_CUSTOM_CLASS "WinWindowClass"

WinWindow::WinWindow(Window& window) : m_window(window)
{
    m_size = {800, 600};
    // TODO id
    m_props = m_window.getProps();

    // TODO move to app cycle
    ResourceRegistry::Init();
    std::cout << "> WinWindow::WinWindow Window&\n"; // TODO dev
}

auto WinWindow::create(HINSTANCE hInstance) -> void
{
    m_hInstance = hInstance;

    // TODO move to app cycle
    ClassRegistry::Init(m_hInstance);

    ClassRegistry::Register(
        CUSTOM_CLASS_KEY,
        {
            .name = TEXT(CUSTOM_CLASS_KEY),
            .proc = WindowProc,
            // .background = (HBRUSH)COLOR_HIGHLIGHTTEXT,
            // TODO set window icon
            .icon = LoadIcon(m_hInstance, MAKEINTRESOURCE(101)),
            // .icon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_APP_ICON)),
        }
    );

    createNative({});

    std::cout << "> WinWindow::create hInstance\n"; // TODO dev
}

auto WinWindow::create(ApiWidget& parent) -> void
{
    std::cout << "WinWindow::create ApiWidget&\n";

    auto& winParent = static_cast<WinWidget&>(parent);
    HWND hwndParent = winParent.handle();

    // createNative({});

    // TODO set Title
    // SetWindowText(m_hwnd, toNativeString(m_props.title).c_str());
}

auto WinWindow::initPosition() -> Point
{
    auto result = Point{CW_USEDEFAULT, CW_USEDEFAULT};

    if (m_props.position.x >= 0)
    {
        result.x = m_props.position.x;
    }

    if (m_props.position.y >= 0)
    {
        result.y = m_props.position.y;
    }

    return result;
}

auto WinWindow::exStyle() const -> DWORD
{
    auto exStyle = 0; // WS_EX_ACCEPTFILES

    // exStyle |= WS_EX_LAYERED; // +alphe

    return exStyle;
}


auto WinWindow::style() const -> DWORD
{
    auto style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | SS_NOTIFY; // | WS_CLIPCHILDREN;

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

auto WinWindow::createNative(const Rect rect) -> HWND
{
    auto startPos = initPosition();

    m_hwnd = CreateWindowEx(
        exStyle(),
        ClassRegistry::Get(CUSTOM_CLASS_KEY),
        m_props.title.c_str(),
        style(),
        // TODO remember size / position
        // TODO center
        startPos.x, startPos.y,
        m_props.size.width, m_props.size.height,
        parentHandle(),
        // nullptr, // HWND_DESKTOP, //  create parent window?
        nullptr,
        m_hInstance,
        this);

    if (!m_hwnd)
    {
        std::cerr << "[Error] WinWindow::CreateNative " << GetLastError() << std::endl;
    }

    // SetLayeredWindowAttributes(m_hwnd, 0, (255 * 70) / 100, LWA_ALPHA);
    // SetLayeredWindowAttributes(m_hwnd, 0, 128, LWA_ALPHA);
    // SetLayeredWindowAttributes(m_hwnd, RGB(255, 0, 0), 128, LWA_COLORKEY);

    return m_hwnd;
}

auto WinWindow::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    switch (msg)
    {
    // case WM_CREATE:
    //     {
    //         // CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
    //         // int width = pCreate->cx;
    //         // int height = pCreate->cy;
    //         // int x = pCreate->x;
    //         // int y = pCreate->y;
    //         return 0;
    //     }

    case WM_COMMAND:
        return Backend::CommandHandler::Handle(*this, wParam, lParam);

    case WM_MOUSEMOVE: // WM_NCMOUSEMOVE ?
    case WM_LBUTTONDBLCLK:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDBLCLK:
    case WM_MOUSEWHEEL:
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_CHAR:
        return Backend::InputHandler::Handle(*this, msg, wParam, lParam);

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

    case WM_NCHITTEST: // TODO
        {
            // return HTTRANSPARENT; // TODO TOTAL ignore
            LRESULT hit = DefWindowProc(hwnd, msg, wParam, lParam);
            if (hit == HTCLIENT)
            {
                // POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
                // ScreenToClient(hwnd, &pt);
                // if (pt.y < 32) return HTCAPTION;

                return HTCAPTION; // TODO! Mouse events Blocker!
            }
            return hit;
        }


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
            // // #ifdef BLADE_DEBUG_LAYOUT
            // PAINTSTRUCT ps;
            // HDC hdc = BeginPaint(hwnd, &ps);
            // LayoutDebugRenderer::Render(hdc, *m_owner->m_root);
            // EndPaint(hwnd, &ps);
            // // #endif
            // return 0;

            return Backend::PaintHandler::Handle(*this, wParam, lParam);
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
    case WM_SIZE:
    case WM_DESTROY:
        Backend::WindowHandler::Handle(*this, msg, wParam, lParam);
        break;


    case WM_NCDESTROY:
        {
            SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
            m_hwnd = nullptr;
            return 0;
        }
    }

    return WinWidget::handleMessage(hwnd, msg, wParam, lParam);
}

auto WinWindow::show() const -> void
{
    ShowWindow(m_hwnd, SW_SHOW);
}

auto WinWindow::resize(Size size) -> void
{
    m_size = size;
    m_window.resize(m_size);
}

auto WinWindow::onDestroy() const -> void
{
    m_window.destroy();
}


} // namespace
