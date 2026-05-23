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
                    Api::Logger::Debug(
                        L" -> Apply::",
                        to_string(key),
                        L" ",
                        to_string(*rect)
                    );

                    NativeApi::SetRect(hwnd, *rect);
                }
            }
            break;
        case Api::Props::Title:
            {
                if (const auto* text = std::get_if<Api::Text>(&value))
                {
                    Api::Logger::Debug(
                        L" -> Apply::",
                        to_string(key),
                        L" [",
                        text->c_str(),
                        L"]"
                    );

                    NativeApi::SetTitle(hwnd, *text);
                }
            }
            break;
        case Api::Props::Size:
            {
                if (const auto* size = std::get_if<Api::Size>(&value))
                {
                    Api::Logger::Debug(
                        L" -> Apply::",
                        to_string(key),
                        L" ",
                        to_string(*size)
                    );

                    NativeApi::SetSize(hwnd, *size);
                }
            }
            break;
        case Api::Props::Position:
            {
                if (const auto* point = std::get_if<Api::Point>(&value))
                {
                    Api::Logger::Debug(
                        L" -> Apply::",
                        to_string(key),
                        L" ",
                        to_string(*point)
                    );

                    NativeApi::SetPosition(hwnd, *point);
                }
            }
            break;
        default:
            Api::Logger::Debug(
                L" > Props::",
                to_string(key)
            );
        }
    }
}


} // namespace
