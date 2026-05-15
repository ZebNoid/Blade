#pragma once

#include "../NativeWidget/NativeWidget.h"


class NativeWindow : public NativeWidget
{
public:
    NativeWindow();

    auto create(const WidgetContext& ctx, class Window* owner, const std::string& title) -> void;

protected:
    auto exStyle() const -> DWORD override;
    auto style() const -> DWORD override;

    auto createNative(Rect rect) -> HWND override;
    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

    auto handleCommandMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    auto setRect(Rect rect) -> void;

public:
    auto setTitle(const std::string& title) -> void;
    auto setSize(Size size) -> void;

    auto show() -> void;

protected:
    std::string m_title;
    Window* m_owner = nullptr;
};
