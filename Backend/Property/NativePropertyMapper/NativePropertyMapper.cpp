#include "NativePropertyMapper.h"

#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {


auto NativePropertyMapper::Apply(
    HWND hwnd,
    const Api::PropertyMap& props
) -> void
{
    const auto positionIt =
        props.find(Api::Props::Position);

    const auto sizeIt =
        props.find(Api::Props::Size);

    if (positionIt != props.end() &&
        sizeIt != props.end())
    {
        const auto* point =
            std::get_if<Api::Point>(
                &positionIt->second
            );

        const auto* size =
            std::get_if<Api::Size>(
                &sizeIt->second
            );

        if (point && size)
        {
            std::wcout << " -> Apply::Rect ["
                << point->x << " x "
                << point->y << " | "
                << size->width << " x "
                << size->height << "]\n";

            NativeApi::SetRect(
                hwnd,
                Api::Rect{
                    *point,
                    *size
                }
            );
        }
    }

    for (const auto& [key, value] : props)
    {
        switch (key)
        {
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
                if (positionIt != props.end())
                {
                    break;
                }

                if (const auto* size = std::get_if<Api::Size>(&value))
                {
                    std::wcout << " -> Apply::" << to_string(key) << " [" << size->width << " x " << size->height << "]\n";
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
                if (sizeIt != props.end())
                {
                    break;
                }

                if (const auto* point = std::get_if<Api::Point>(&value))
                {
                    std::wcout << " -> Apply::" << to_string(key) << " [" << point->x << " x " << point->y << "]\n";
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
