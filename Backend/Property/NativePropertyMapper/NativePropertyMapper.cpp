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
        if (key == Api::Props::Title)
        {
            if (const auto* text =
                std::get_if<Api::Text>(&value))
            {
                NativeApi::setTitle(node.hwnd, *text);
            }

            continue;
        }

        if (key == Api::Props::Size)
        {
            if (const auto* size =
                std::get_if<Api::Size>(&value))
            {
                NativeApi::setSize(node.hwnd, *size);
            }

            continue;
        }
    }
}


} // namespace
