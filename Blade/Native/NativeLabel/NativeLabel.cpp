#include "NativeLabel.h"

#include "../Registry/ClassRegistry/ClassRegistry.h"
#include "../Registry/ResourceRegistry/ResourceRegistry.h"


auto NativeLabel::create(const WidgetContext& ctx, const std::string& text) -> void
{
    m_ctx = ctx;
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
    m_font = ResourceRegistry::get_font("system");
    applyFont(m_font);
}

auto NativeLabel::createNative(const Rect rect) -> HWND
{
    m_hwnd = CreateWindowEx(
        0,
        ClassRegistry::Get("BladeLabel"),
        L"",
        WS_CHILD | WS_VISIBLE,
        rect.x,
        rect.y,
        rect.width,
        rect.height,
        m_ctx.hwnd,
        nullptr, // OD
        m_ctx.app->hInstance,
        this
    );

    // m_hwnd = CreateWindowEx(
    //     0,
    //     L"STATIC", // Classic system Label
    //     toNativeString(m_text).c_str(),
    //     // TODO text align
    //     // hAlign SS_LEFT || SS_CENTER ||  SS_RIGHT
    //     // vAlign SS_CENTERIMAGE
    //     // ellipsis SS_WORDELLIPSIS || SS_ENDELLIPSIS
    //     WS_VISIBLE | WS_CHILD | SS_WORDELLIPSIS | SS_CENTERIMAGE | SS_CENTER,
    //     rect.x, rect.y,
    //     rect.width, rect.height,
    //     m_ctx.hwnd,
    //     nullptr, // ID
    //     m_ctx.app->hInstance,
    //     nullptr);

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

            DrawTextW(
                hdc,
                text.c_str(),
                -1,
                &rc,
                DT_CENTER |
                DT_VCENTER |
                DT_SINGLELINE |
                DT_END_ELLIPSIS
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

auto NativeLabel::setRect(const Rect rect) -> void
{
    SetWindowPos(m_hwnd, nullptr, rect.x, rect.y, rect.width, rect.height, SWP_NOZORDER);
}
