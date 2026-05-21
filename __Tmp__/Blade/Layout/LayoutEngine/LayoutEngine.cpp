#include "LayoutEngine.h"

#include "Layout/LayoutFlex/LayoutFlex.h"
#include "Layout/LayoutStack/LayoutStack.h"


namespace Blade {


auto LayoutEngine::Measure(const LayoutContext& ctx) -> Size
{
    switch (ctx.type)
    {
    case LayoutType::Flex:
        {
            return LayoutFlex::Measure(
                ctx.direction,
                *ctx.children,
                *ctx.layout,
                ctx.gap,
                ctx.available
            );
        }

    case LayoutType::Stack:
        {
            return LayoutStack::Measure(
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
            LayoutFlex::Arrange(
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
            LayoutStack::Arrange(
                *ctx.children,
                *ctx.layout,
                ctx.rect
            );

            break;
        }
    }
}

} // namespace
