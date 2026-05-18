#include "LayoutEngine.h"

#include "Layout/FlexLayout/FlexLayout.h"
#include "Layout/StackLayout/StackLayout.h"


namespace Blade {


auto LayoutEngine::Measure(
    LayoutType type,
    FlexDirection direction,
    const std::vector<std::unique_ptr<Widget>>& children,
    const LayoutProps& layout,
    int gap,
    Size available
) -> Size
{
    switch (type)
    {
    case LayoutType::Flex:
        {
            return FlexLayout::Measure(
                direction,
                children,
                layout,
                gap,
                available
            );
        }

    case LayoutType::Stack:
        {
            return StackLayout::Measure(
                children,
                layout,
                available
            );
        }
    }

    return {};
}

auto LayoutEngine::Arrange(
    LayoutType type,
    FlexDirection direction,
    const std::vector<std::unique_ptr<Widget>>& children,
    const LayoutProps& layout,
    MainAxisAlignment mainAxisAlignment,
    CrossAxisAlignment crossAxisAlignment,
    int gap,
    Rect rect
) -> void
{
    switch (type)
    {
    case LayoutType::Flex:
        {
            FlexLayout::Arrange(
                direction,
                children,
                layout,
                mainAxisAlignment,
                crossAxisAlignment,
                gap,
                rect
            );

            break;
        }

    case LayoutType::Stack:
        {
            StackLayout::Arrange(
                children,
                layout,
                rect
            );

            break;
        }
    }
}

} // namespace
