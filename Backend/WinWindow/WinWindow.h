#pragma once


#include "WidgetsProps/Window/WindowProps.h"
#include "Windows/Window/Window.h"
#include "WinWidget/WinWidget.h"


namespace Blade::Backend {


class WinWindow : public WinWidget
{
public:
    // WinWindow(WinWindow&&) = default;
    // WinWindow(); // TODO
    explicit WinWindow(Window& window);

    // auto create(const WidgetContext& ctx, Window* owner, const WindowProps& props) -> void;
    auto create(HINSTANCE hInstance) -> void;

protected:
    auto exStyle() const -> DWORD override;

    auto style() const -> DWORD override;

    auto widgetName() const -> std::string override { return "NativeWindow"; }

    auto createNative(Rect rect) -> HWND override;

    auto initPosition() -> Point;

    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

public:
    auto show() const -> void;

    auto owner() const -> Window*
    {
        return &m_window;
    }

    auto resize(Size size) -> void;

    auto onDestroy() const -> void;

protected:
    Window& m_window;
    WindowProps m_props{};

    HINSTANCE m_hInstance;
};


} // namespace
