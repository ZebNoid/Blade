#include "CommandHandler.h"
#include "../../../../Backend/WinWindow/WinWindow.h"


namespace Blade::Backend::WinApi {


auto CommandHandler::Handle(WinWindow& window, WPARAM wParam, LPARAM lParam) -> LRESULT
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

            // window.owner()->dispatchCommand(id, WidgetEvent::Change, Utf16ToUtf8(buffer)); // TODO!!!

            VerticalAlignCenter(currentHwnd); // TODO dev
        }
        break;

    case EN_SETFOCUS:
        // window.owner()->dispatchCommand(id, WidgetEvent::Focus, true); // TODO!!!
        break;

    case EN_KILLFOCUS:
        // window.owner()->dispatchCommand(id, WidgetEvent::Focus, false); // TODO!!!
        break;

    case BN_CLICKED:
        {
            LONG_PTR style = GetWindowLongPtr(currentHwnd, GWL_STYLE);
            LONG_PTR type = style & BS_TYPEMASK;

            if (type == BS_AUTOCHECKBOX)
            {
                LRESULT state = SendMessage(currentHwnd, BM_GETCHECK, 0, 0);
                auto isChecked = state == BST_CHECKED;
                // window.owner()->dispatchCommand(id, WidgetEvent::Change, isChecked); // TODO!!!
            }
            else if (type == BS_AUTORADIOBUTTON)
            {
                LRESULT state = SendMessage(currentHwnd, BM_GETCHECK, 0, 0);
                auto isChecked = state == BST_CHECKED;
                // window.owner()->dispatchCommand(id, WidgetEvent::Change, isChecked); // TODO!!!
            }
            else
            {
                // window.owner()->dispatchCommand(id, WidgetEvent::Click); // TODO!!!
            }
        }
        break;

    default: ;
    }
    return 0;
}

} // namespace
