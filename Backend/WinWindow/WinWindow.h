#pragma once


#include "Backend/NativeWidget/NativeWidget.h"
#include "WidgetsProps/Window/WindowProps.h"
#include "Windows/Window/Window.h"


namespace Blade {


class WinWindow : public NativeWidget
{
public:
    WinWindow();

    auto create(const WidgetContext& ctx, class Window* owner, const WindowProps& props) -> void;

protected:
    auto exStyle() const -> DWORD override;

    auto style() const -> DWORD override;

    auto widgetName() const -> std::string override { return "NativeWindow"; }

    auto createNative(Rect rect) -> HWND override;

    Point initPosition();

    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

public:
    auto show() const -> void;

    auto owner() const -> Window*
    {
        return m_owner;
    }

    auto resize(Size size) -> void;

    auto onDestroy() const -> void;

protected:
    Window* m_owner = nullptr;
    WindowProps m_props{};
};


} // namespace
