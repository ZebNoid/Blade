#include "NativePropertyMapper.h"

#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {


auto NativePropertyMapper::apply(
    NativeNode& node,
    const Api::PropertyMap& props
) -> void
{
    for (const auto& [key, value] : props)
    {
        switch (key)
        {
        case Api::Props::Title:
            {
                if (const auto* text =
                    std::get_if<Api::Text>(&value))
                {
                    NativeApi::SetTitle(node.hwnd, *text);
                }
            }
            break;
        case Api::Props::Size:
            {
                if (const auto* size =
                    std::get_if<Api::Size>(&value))
                {
                    NativeApi::SetSize(node.hwnd, *size);
                }
            }
            break;
        case Api::Props::Position:
            {
                if (const auto* point =
                    std::get_if<Api::Point>(&value))
                {
                    NativeApi::SetPosition(node.hwnd, *point);
                }
            }
            break;
        default:
            std::wcout << "Props::" << to_string(key) << std::endl;;
        }
    }
}


} // namespace
