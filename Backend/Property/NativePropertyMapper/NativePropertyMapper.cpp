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
        case Api::Props::Rect:
            {
                if (const auto* rect = std::get_if<Api::Rect>(&value))
                {
                    std::wcout << " -> Apply::" << to_string(key) << " "
                        << to_string(*rect) << "\n";

                    NativeApi::SetRect(hwnd, *rect);
                }
            }
            break;
        case Api::Props::Title:
            {
                if (const auto* text = std::get_if<Api::Text>(&value))
                {
                    std::wcout << " -> Apply::" << to_string(key) << " [" << text->c_str() << "]\n";
                    NativeApi::SetTitle(hwnd, *text);
                }
            }
            break;
        case Api::Props::Size:
            {
                if (const auto* size = std::get_if<Api::Size>(&value))
                {
                    std::wcout << " -> Apply::" << to_string(key) << " "
                        << to_string(*size) << "\n";
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
                    std::wcout << " -> Apply::" << to_string(key) << " "
                        << to_string(*point) << "\n";
                    NativeApi::SetPosition(hwnd, *point);
                }
            }
            break;
        default:
            std::wcout << " > Props::" << to_string(key) << std::endl;
        }
    }
}


} // namespace
