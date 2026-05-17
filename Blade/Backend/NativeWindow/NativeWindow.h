#pragma once

#include "Backend/NativeWidget/NativeWidget.h"
#include "Props/Window/WindowProps.h"


namespace Blade {


class NativeWindow : public NativeWidget
{
public:
    NativeWindow();

    auto create(const WidgetContext& ctx, class Window* owner, const WindowProps& props) -> void;

protected:
    auto exStyle() const -> DWORD override;

    auto style() const -> DWORD override;

    auto widgetName() const -> std::string override { return "NativeWindow"; }

    auto createNative(Rect rect) -> HWND override;

    auto setProps(const WindowProps& props) -> void
    {
        m_props = props;
    }

    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

public:
    auto setSize(Size size) -> void;

    auto show() -> void;

    auto getOwner() const -> Window*
    {
        return m_owner;
    }

protected:
    Window* m_owner = nullptr;
    WindowProps m_props{};
};


} // namespace
