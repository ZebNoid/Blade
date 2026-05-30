#include "LayoutFlexTests.h"

#include "Core/Expect.h"
#include "Layout/LayoutTestUtils.h"
#include "Widget/Label/Label.h"
#include "Widget/Layout/Column/Column.h"
#include "Widget/Layout/Row/Row.h"

namespace Blade::Tests {

namespace {

auto RowSplitsFlexSpace() -> void
{
    auto layout = BuildLayout(
        Row(
            Label(L"Left").flex(1),
            Label(L"Right").flex(2)
        ).tree(),
        {300, 100}
    );

    ExpectEqual(layout.children.at(0).rect.width, 100, "row flex first width");
    ExpectEqual(layout.children.at(1).rect.x, 100, "row flex second x");
    ExpectEqual(layout.children.at(1).rect.width, 200, "row flex second width");
}

auto ColumnSplitsFlexSpaceWithGap() -> void
{
    auto layout = BuildLayout(
        Column(
            Label(L"Top").flex(1),
            Label(L"Bottom").flex(1)
        ).gap(8).tree(),
        {100, 108}
    );

    ExpectEqual(layout.children.at(0).rect.height, 50, "column flex first height");
    ExpectEqual(layout.children.at(1).rect.y, 58, "column flex second y");
    ExpectEqual(layout.children.at(1).rect.height, 50, "column flex second height");
}

auto FixedChildKeepsSizeBeforeFlexSpace() -> void
{
    auto layout = BuildLayout(
        Row(
            Label(L"Fixed").maxSize({60, 0}),
            Label(L"Flex").flex(1)
        ).gap(10).tree(),
        {200, 100}
    );

    ExpectEqual(layout.children.at(0).rect.width, 60, "fixed child width");
    ExpectEqual(layout.children.at(1).rect.x, 70, "flex child x after gap");
    ExpectEqual(layout.children.at(1).rect.width, 130, "flex child width after fixed");
}

} // namespace

auto RunLayoutFlexTests() -> void
{
    RowSplitsFlexSpace();
    ColumnSplitsFlexSpaceWithGap();
    FixedChildKeepsSizeBeforeFlexSpace();
}

} // namespace Blade::Tests
