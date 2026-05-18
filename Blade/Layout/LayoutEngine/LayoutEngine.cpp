#include "LayoutEngine.h"

#include "Layout/FlexLayout/FlexLayout.h"
#include "Layout/StackLayout/StackLayout.h"


namespace Blade {


auto LayoutEngine::Measure(const LayoutContext& ctx) -> Size
{
    switch (ctx.type)
    {
    case LayoutType::Flex:
        {
            return FlexLayout::Measure(
                ctx.direction,
                *ctx.children,
                *ctx.layout,
                ctx.gap,
                ctx.available
            );
        }

    case LayoutType::Stack:
        {
            return StackLayout::Measure(
                *ctx.children,
                *ctx.layout,
                ctx.available
            );
        }
    }

    return {};
}

auto LayoutEngine::Arrange(const LayoutContext& ctx) -> void
{
    switch (ctx.type)
    {
    case LayoutType::Flex:
        {
            FlexLayout::Arrange(
                ctx.direction,
                *ctx.children,
                *ctx.layout,
                ctx.mainAxisAlignment,
                ctx.crossAxisAlignment,
                ctx.gap,
                ctx.rect
            );

            break;
        }

    case LayoutType::Stack:
        {
            StackLayout::Arrange(
                *ctx.children,
                *ctx.layout,
                ctx.rect
            );

            break;
        }
    }
}

} // namespace
