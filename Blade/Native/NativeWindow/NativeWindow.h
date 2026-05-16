#pragma once

#include "Native/NativeWidget/NativeWidget.h"
#include "Props/Window/WindowProps.h"


class NativeWindow : public NativeWidget
{
public:
    NativeWindow();

    auto create(const WidgetContext& ctx, class Window* owner, const WindowProps& props) -> void;

protected:
    auto exStyle() const -> DWORD override;
    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;

    auto setRect(Rect rect) -> void;

    auto setProps(const WindowProps& props) -> void
    {
        m_props = props;
    }

    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;
    auto handleCommandMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

public:
    auto setSize(Size size) -> void;
    auto show() -> void;

protected:
    Window* m_owner = nullptr;

    WindowProps m_props{};
};
