#include "NativeCustom.h"

#include "Backend/Registry/ClassRegistry/ClassRegistry.h"


namespace Blade {

#define CUSTOM_CLASS_KEY "NativeCustom"
#define NATIVE_CUSTOM_CLASS "NativeCustomClass"

auto NativeCustom::create(
    const WidgetContext& ctx,
    WidgetId id) -> void
{
    m_ctx = ctx;
    m_id = id;


    ClassRegistry::Register(
        NATIVE_CUSTOM_CLASS,
        {
            .name = TEXT(CUSTOM_CLASS_KEY),
            .proc = WindowProc,
            .background = nullptr
        }
    );

    createNative(Rect{0, 0, 140, 32});
    // m_font = ResourceRegistry::GetFont("system");
}

DWORD NativeCustom::style() const
{
    auto style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
    return style;
}

DWORD NativeCustom::exStyle() const
{
    auto exStyle = 0; //WS_EX_TRANSPARENT;
    return exStyle;
}

auto NativeCustom::createNative(const Rect rect) -> HWND
{
    NativeWidget::createNative(rect);
    if (m_ctx.hwnd == nullptr) return nullptr;

    m_hwnd = CreateWindowEx(
        exStyle(),
        ClassRegistry::Get(NATIVE_CUSTOM_CLASS),
        TEXT(""),
        style(),
        rect.x, rect.y,
        rect.width, rect.height,
        m_ctx.hwnd,
        nullptr, // ID
        m_ctx.app->hInstance,
        this
    );

    if (!m_hwnd)
    {
        std::cerr << "[Error] NativeCustom::CreateNative " << GetLastError() << std::endl;
    }
    return m_hwnd;
}

auto NativeCustom::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
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



            EndPaint(hwnd, &ps);

            return 0;
        }

    case WM_NCHITTEST:
        return HTTRANSPARENT; // All hits pass through
    }

    return NativeWidget::handleMessage(hwnd, msg, wParam, lParam);
}


} // namespace
