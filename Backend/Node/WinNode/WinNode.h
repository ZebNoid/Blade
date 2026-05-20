#pragma once

#include <string>
#include <windows.h>

#include "Common/Common.h"


namespace Blade::Backend {


class WinNode
{

};


struct NativeWidgetDesc
{
    std::wstring className;
    std::wstring text;

    DWORD style = 0;
    DWORD exStyle = 0;

    Api::Rect rect{};
    Api::Id id{};
};

} // namespace
