#include "LayoutEngine.h"

#include "Runtime/LayoutEngine/Algorithm/LayoutColumn/LayoutColumn.h"
#include "Runtime/LayoutEngine/Algorithm/LayoutLeaf/LayoutLeaf.h"
#include "Runtime/LayoutEngine/Algorithm/LayoutRow/LayoutRow.h"
#include "Runtime/LayoutEngine/Algorithm/LayoutStack/LayoutStack.h"
#include "Runtime/LayoutEngine/Algorithm/LayoutVirtual/LayoutVirtual.h"


namespace Blade::Layout::Engine {

auto Measure(LayoutContext& ctx) -> Api::Size
{
    auto& node = *ctx.node;

    switch (node.layoutType)
    {
    case LayoutType::Column:
        return Layout::Column::Measure(ctx);

    case LayoutType::Row:
        return Layout::Row::Measure(ctx);

    case LayoutType::Stack:
        return Layout::Stack::Measure(ctx);

    case LayoutType::Virtual:
        return Layout::Virtual::Measure(ctx);

    case LayoutType::None:
    default:
        return Layout::Leaf::Measure(ctx);
    }
}

auto Arrange(LayoutContext& ctx) -> void
{
    auto& node = *ctx.node;

    node.rect = ctx.rect;

    switch (node.layoutType)
    {
    case LayoutType::Column:
        Layout::Column::Arrange(ctx);
        break;

    case LayoutType::Row:
        Layout::Row::Arrange(ctx);
        break;

    case LayoutType::Stack:
        Layout::Stack::Arrange(ctx);
        break;

    case LayoutType::Virtual:
        Layout::Virtual::Arrange(ctx);
        break;

    default:
        Layout::Leaf::Arrange(ctx);
        break;
    }
}

} // namespace Blade::Layout::Engine
