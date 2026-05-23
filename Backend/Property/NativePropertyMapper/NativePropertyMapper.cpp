#include "NativePropertyMapper.h"

#include "Common/Logger.h"
#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {


auto NativePropertyMapper::Apply(
    HWND hwnd,
    const Api::PropertyMap& props
) -> void
{
    for (const auto& [key, value] : props)
    {
        switch (key)
        {
        case Api::Props::Rect:
            {
                if (const auto* rect = std::get_if<Api::Rect>(&value))
                {
                    LOG_DF(L" -> Apply::%s %s", to_string(key).c_str(), to_string(*rect).c_str());

                    NativeApi::SetRect(hwnd, *rect);
                }
            }
            break;
        case Api::Props::Title:
            {
                if (const auto* text = std::get_if<Api::Text>(&value))
                {
                    LOG_DF(L" -> Apply::%s [%s]", to_string(key).c_str(), text->c_str());

                    NativeApi::SetTitle(hwnd, *text);
                }
            }
            break;
        case Api::Props::Size:
            {
                if (const auto* size = std::get_if<Api::Size>(&value))
                {
                    LOG_DF(L" -> Apply::%s %s", to_string(key).c_str(), to_string(*size).c_str());

                    NativeApi::SetSize(hwnd, *size);
                }
            }
            break;
        case Api::Props::Position:
            {
                if (const auto* point = std::get_if<Api::Point>(&value))
                {
                    LOG_DF(L" -> Apply::%s %s", to_string(key).c_str(), to_string(*point).c_str());

                    NativeApi::SetPosition(hwnd, *point);
                }
            }
            break;
        default:
            LOG_DF(L" > Props::%s", to_string(key).c_str());
        }
    }
}


} // namespace
