#pragma once

#include <commctrl.h>
#include <shellapi.h>

#include "Common/Types.h"

namespace Blade::Backend {

class NativeTrayApi
{
public:
    static auto Notify(DWORD message, NOTIFYICONDATAW& data, Api::Id id) -> bool;
    static auto SetSubclass(HWND hwnd, SUBCLASSPROC proc, DWORD_PTR data) -> void;
    static auto RemoveSubclass(HWND hwnd, SUBCLASSPROC proc) -> void;
    static auto DestroyIcon(HICON icon) -> void;
};

} // namespace Blade::Backend
