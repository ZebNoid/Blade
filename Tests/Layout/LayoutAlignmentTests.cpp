#include "LayoutAlignmentTests.h"

#include "Core/Expect.h"
#include "Layout/LayoutTestUtils.h"
#include "Widget/Label/Label.h"
#include "Widget/Layout/Column/Column.h"
#include "Widget/Layout/Row/Row.h"

namespace Blade::Tests {

namespace {

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

auto ColumnAlignsChildToEndHorizontally() -> void
{
    auto layout = BuildLayout(
        Column(Label(L"Text"))
            .horizontalAlignment(CrossAxisAlignment::End)
            .tree(),
        {200, 100}
    );

    const auto& label = layout.children.at(0);
    ExpectEqual(label.rect.x, 80, "column end label.rect.x");
    ExpectEqual(label.rect.width, 120, "column end label.rect.width");
}

auto RowAlignsChildToEndVertically() -> void
{
    auto layout = BuildLayout(
        Row(Label(L"Text"))
            .verticalAlignment(CrossAxisAlignment::End)
            .tree(),
        {200, 100}
    );

    const auto& label = layout.children.at(0);
    ExpectEqual(label.rect.y, 76, "row end label.rect.y");
    ExpectEqual(label.rect.height, 24, "row end label.rect.height");
}

auto ColumnStretchesChildHorizontallyByDefault() -> void
{
    auto layout = BuildLayout(
        Column(Label(L"Text")).tree(),
        {200, 100}
    );

    const auto& label = layout.children.at(0);
    ExpectEqual(label.rect.x, 0, "column stretch label.rect.x");
    ExpectEqual(label.rect.width, 200, "column stretch label.rect.width");
}

} // namespace

auto RunLayoutAlignmentTests() -> void
{
    ColumnAlignsVerticallyAndHorizontally();
    RowAlignsHorizontallyAndVertically();
    ColumnAlignsChildToEndHorizontally();
    RowAlignsChildToEndVertically();
    ColumnStretchesChildHorizontallyByDefault();
}

} // namespace Blade::Tests
