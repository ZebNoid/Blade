#pragma once

#include "../NativeWidget/NativeWidget.h"


class NativeWindow : public NativeWidget
{
public:
    NativeWindow();

    auto Create(const WidgetContext& ctx, class Window* owner, const std::string& title) -> void;

protected:
    auto ExStyle() const -> DWORD override;
    auto Style() const -> DWORD override;

    auto CreateNative(Rect rect) -> HWND override;
    auto HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

    auto HandleCommandMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    auto SetRect(Rect rect) -> void;

public:
    auto SetTitle(const std::string& title) -> void;
    auto SetSize(Size size) -> void;

    auto Show() -> void;

protected:
    std::string m_title;
    Window* m_owner = nullptr;
};
