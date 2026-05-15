#pragma once

#include "../NativeWidget/NativeWidget.h"


class NativeLabel : public NativeWidget
{
public:
    NativeLabel() = default;

    auto Create(const WidgetContext& ctx, const std::string& text) -> void;

protected:
    auto CreateNative(Rect rect) -> HWND override;

    auto HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

private:
    std::string m_text;
    HFONT m_font = nullptr;

public:
    auto SetRect(Rect rect) -> void;
};
