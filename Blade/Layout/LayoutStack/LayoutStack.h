#pragma once
#include <vector>


namespace Blade {


class LayoutStack
{
public:
    static auto Measure(
        const std::vector<std::unique_ptr<Widget>>& children,
        const LayoutProps& layout,
        Size available
    ) -> Size;

    static auto Arrange(
        const std::vector<std::unique_ptr<Widget>>& children,
        const LayoutProps& layout,
        Rect rect
    ) -> void;
};

} // namespace
