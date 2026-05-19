#include "WinCustom.h"

#include "Registry/ClassRegistry/ClassRegistry.h"
#include "Registry/ResourceRegistry/ResourceRegistry.h"


namespace Blade::Backend {

#define CUSTOM_CLASS_KEY "WinCustom"
#define NATIVE_CUSTOM_CLASS "WinCustomClass"

WinCustom::WinCustom(Widget& widget)
{
    std::cout << " -> WinCustom::create Widget&\n"; // TODO dev
}

auto WinCustom::create(ApiWidget& parent) -> void
{
    std::cout << " -> WinCustom::create ApiWidget&\n"; // TODO dev
    m_parent = &parent;
    // create(0);
}

auto WinCustom::create(WidgetId id) -> void
{
    std::cout << " -> WinCustom::create id\n"; // TODO dev
    m_id = id;
    m_systemFont = ResourceRegistry::GetFont("system");

    ClassRegistry::Register(
        NATIVE_CUSTOM_CLASS,
        {
            .name = TEXT(CUSTOM_CLASS_KEY),
            .proc = WindowProc,
            .background = nullptr
        }
    );

    createNative(Rect{0, 0, 140, 32}); // TODO rect? its ignored anyway
    applyFont(m_systemFont);
}

DWORD WinCustom::style() const
{
    auto style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
    return style;
}

DWORD WinCustom::exStyle() const
{
    auto exStyle = 0; //WS_EX_TRANSPARENT;
    return exStyle;
}

auto WinCustom::createNative(const Rect rect) -> HWND
{
    m_hwnd = CreateWindowEx(
        exStyle(),
        ClassRegistry::Get(NATIVE_CUSTOM_CLASS),
        TEXT(""),
        style(),
        0, 0, 0, 0, // TODO why?
        // rect.x, rect.y,
        // rect.width, rect.height,
        parentHandle(),
        nullptr, // ID
        GetModuleHandle(nullptr), // TODO m_ctx.app->hInstance,
        this
    );

    if (!m_hwnd)
    {
        std::cerr << "[Error] WinCustom::CreateNative " << GetLastError() << std::endl;
    }
    return m_hwnd;
}

auto WinCustom::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    switch (msg)
    {
    case WM_ERASEBKGND:
        return TRUE; // Stop the OS from erasing the background

    case WM_PAINT:
        {
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

    return WinWidget::handleMessage(hwnd, msg, wParam, lParam);
}


} // namespace
