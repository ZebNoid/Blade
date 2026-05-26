#include "PropertyMapper.h"

#include "Common/Logger.h"
#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {

auto PropertyMapper::Apply(HWND hwnd, const Api::PropertyMap& props) -> void
{
    for (const auto& [key, value] : props)
    {
        switch (key)
        {
        case Api::Props::Rect:
            {
                if (const auto* rect = std::get_if<Api::Rect>(&value))
                {
                    LOGF_D(L" -> ApplyProps::%s %s", to_string(key).c_str(), to_string(*rect).c_str());
                    NativeApi::SetRect(hwnd, *rect);
                }
            }
            break;
        case Api::Props::Title:
            {
                if (const auto* text = std::get_if<Api::Text>(&value))
                {
                    LOGF_D(L" -> ApplyProps::%s [%s]", to_string(key).c_str(), text->c_str());
                    NativeApi::SetTitle(hwnd, *text);
                }
            }
            break;
        case Api::Props::Size:
            {
                if (const auto* size = std::get_if<Api::Size>(&value))
                {
                    LOGF_D(L" -> ApplyProps::%s %s", to_string(key).c_str(), to_string(*size).c_str());
                    NativeApi::SetSize(hwnd, *size);
                }
            }
            break;
        case Api::Props::Position:
            {
                if (const auto* point = std::get_if<Api::Point>(&value))
                {
                    LOGF_D(L" -> ApplyProps::%s %s", to_string(key).c_str(), to_string(*point).c_str());
                    NativeApi::SetPosition(hwnd, *point);
                }
            }
            break;
        case Api::Props::Visible:
            {
                if (const auto* visible = std::get_if<bool>(&value))
                {
                    LOGF_D(L" -> ApplyProps::%s %d", to_string(key).c_str(), *visible);
                    NativeApi::SetVisible(hwnd, *visible);
                }
            }
            break;
        case Api::Props::IsDefault:
            break;
        default:
            LOGF_W(L" -> ApplyProps::%s not implemented", to_string(key).c_str());
        }
    }
}

} // namespace Blade::Backend
