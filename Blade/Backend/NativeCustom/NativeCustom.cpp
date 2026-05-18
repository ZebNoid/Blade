#include "NativeCustom.h"

#include "Backend/Registry/ClassRegistry/ClassRegistry.h"


namespace Blade {

#define CUSTOM_CLASS_KEY "NativeCustom"
#define NATIVE_CUSTOM_CLASS "NativeCustomClass"

auto NativeCustom::create(
    const WidgetContext& ctx,
    WidgetId id
) -> void
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

    createNative(Rect{0, 0, 140, 32}); // TODO rect? its ignored anyway
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
        0,0,0,0, // TODO why?
        // rect.x, rect.y,
        // rect.width, rect.height,
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
            std::cout << "NativeCustom::handleMessage!!\n";
    switch (msg)
    {
    case WM_ERASEBKGND:
        return TRUE; // Stop the OS from erasing the background

    case WM_PAINT:
        {
            std::cout << "NativeCustom!!\n";
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            SetBkMode(hdc, TRANSPARENT);

            RECT rc;
            GetClientRect(hwnd, &rc);

            paint(hdc, rc);


            EndPaint(hwnd, &ps);

            return 0;
        }

    case WM_NCHITTEST:
        // TODO for child class
        return HTTRANSPARENT; // All hits pass through
    }

    return NativeWidget::handleMessage(hwnd, msg, wParam, lParam);
}


} // namespace
