#include "LayoutAlignmentTests.h"

#include "Core/Expect.h"
#include "Runtime/LayoutRuntime/LayoutPass/LayoutPass.h"
#include "Runtime/ModifierTree/ModifierTreeBuilder.h"
#include "Widget/Label/Label.h"
#include "Widget/Layout/Column/Column.h"
#include "Widget/Layout/Row/Row.h"

namespace Blade::Tests {

namespace {

auto BuildLayout(WidgetTree tree, Api::Size available) -> LayoutNode
{
    return LayoutPass::Compute(ModifierTreeBuilder::Expand(std::move(tree)), available);
}

auto ColumnAlignsVerticallyAndHorizontally() -> void
{
    auto layout = BuildLayout(
        Column(Label(L"Text"))
            .verticalAlignment(MainAxisAlignment::Center)
            .horizontalAlignment(CrossAxisAlignment::Center)
            .tree(),
        {200, 200}
    );

    const auto& label = layout.children.at(0);
    ExpectEqual(label.rect.x, 40, "column label.rect.x");
    ExpectEqual(label.rect.y, 88, "column label.rect.y");
    ExpectEqual(label.rect.width, 120, "column label.rect.width");
    ExpectEqual(label.rect.height, 24, "column label.rect.height");
}

auto RowAlignsHorizontallyAndVertically() -> void
{
    auto layout = BuildLayout(
        Row(Label(L"Text"))
            .horizontalAlignment(MainAxisAlignment::Center)
            .verticalAlignment(CrossAxisAlignment::Center)
            .tree(),
        {200, 200}
    );

    const auto& label = layout.children.at(0);
    ExpectEqual(label.rect.x, 40, "row label.rect.x");
    ExpectEqual(label.rect.y, 88, "row label.rect.y");
    ExpectEqual(label.rect.width, 120, "row label.rect.width");
    ExpectEqual(label.rect.height, 24, "row label.rect.height");
}

} // namespace

auto RunLayoutAlignmentTests() -> void
{
    ColumnAlignsVerticallyAndHorizontally();
    RowAlignsHorizontallyAndVertically();
}

} // namespace Blade::Tests
