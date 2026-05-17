#include "CommandHandler.h"
#include "Backend/NativeWindow/NativeWindow.h"


namespace Blade::Backend::WinApi {


auto CommandHandler::Handle(NativeWindow& window, WPARAM wParam, LPARAM lParam) -> LRESULT
{
    const int id = LOWORD(wParam);
    const int event = HIWORD(wParam);
    const auto currentHwnd = (HWND)lParam;

    switch (event)
    {
    case EN_CHANGE:
        {
            const int len = GetWindowTextLength(currentHwnd);
            if (len <= 0) break;

            std::wstring buffer(len + 1, L'\0');
            GetWindowText(currentHwnd, &buffer[0], len + 1);
            // GetWindowText(hEdit, buffer.data(), len + 1);
            window.getOwner()->dispatchCommand(id, WidgetEvent::Change, Utf16ToUtf8(buffer));
            VerticalAlignCenter(currentHwnd); // TODO dev
        }
        break;

    case EN_SETFOCUS:
        window.getOwner()->dispatchCommand(id, WidgetEvent::Focus, true);
        break;

    case EN_KILLFOCUS:
        window.getOwner()->dispatchCommand(id, WidgetEvent::Focus, false);
        break;

    case BN_CLICKED:
        {
            LONG_PTR style = GetWindowLongPtr(currentHwnd, GWL_STYLE);
            LONG_PTR type = style & BS_TYPEMASK;

            if (type == BS_AUTOCHECKBOX)
            {
                LRESULT state = SendMessage(currentHwnd, BM_GETCHECK, 0, 0);
                auto isChecked = state == BST_CHECKED;
                window.getOwner()->dispatchCommand(id, WidgetEvent::Change, isChecked);
            }
            else if (type == BS_AUTORADIOBUTTON)
            {
                LRESULT state = SendMessage(currentHwnd, BM_GETCHECK, 0, 0);
                auto isChecked = state == BST_CHECKED;
                window.getOwner()->dispatchCommand(id, WidgetEvent::Change, isChecked);
            }
            else
            {
                window.getOwner()->dispatchCommand(id, WidgetEvent::Click);
            }
        }
        break;

    default: ;
    }
    return 0;
}

} // namespace
