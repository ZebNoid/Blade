#pragma once
#include <vector>


namespace Blade {

// TODO StackLayout -> LayoutStack
class StackLayout
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
