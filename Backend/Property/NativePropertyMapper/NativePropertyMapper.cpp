#include "NativePropertyMapper.h"

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
        case Api::Props::Title:
            {
                if (const auto* text = std::get_if<Api::Text>(&value))
                {
                    NativeApi::SetTitle(hwnd, *text);
                }
            }
            break;
        case Api::Props::Size:
            {
                if (const auto* size = std::get_if<Api::Size>(&value))
                {
                    NativeApi::SetSize(hwnd, *size);
                    // TODO
                    // auto oldSize = NativeApi::GetSize(hwnd);
                    // NativeApi::SetSize(hwnd, {
                    //     .width = size->width > 0 ? size->width : oldSize.width,
                    //     .height = size->height > 0 ? size->height : oldSize.height,
                    // });
                }
            }
            break;
        case Api::Props::Position:
            {
                if (const auto* point = std::get_if<Api::Point>(&value))
                {
                    NativeApi::SetPosition(hwnd, *point);
                }
            }
            break;
        default:
            std::wcout << "Props::" << to_string(key) << std::endl;;
        }
    }
}


} // namespace
