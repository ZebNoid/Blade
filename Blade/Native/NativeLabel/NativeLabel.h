#pragma once

#include "../NativeWidget/NativeWidget.h"


class NativeLabel : public NativeWidget
{
public:
    NativeLabel() = default;

    auto create(const WidgetContext& ctx, const std::string& text) -> void;

protected:
    auto createNative(Rect rect) -> HWND override;

    auto handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT override;

private:
    std::string m_text;
    HFONT m_font = nullptr;

public:
    auto setRect(Rect rect) -> void;
};
