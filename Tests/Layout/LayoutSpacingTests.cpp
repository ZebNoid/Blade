#include "LayoutSpacingTests.h"

#include "Core/Expect.h"
#include "Layout/LayoutTestUtils.h"
#include "Props/LayoutProps/MainAxisAlignment.h"
#include "Widget/Label/Label.h"
#include "Widget/Layout/Row/Row.h"

namespace Blade::Tests {

namespace {

auto RowSpaceBetweenDistributesFreeSpace() -> void
{
    auto layout = BuildLayout(
        Row(
            Label(L"One").maxSize({40, 20}),
            Label(L"Two").maxSize({40, 20}),
            Label(L"Three").maxSize({40, 20})
        ).horizontalAlignment(MainAxisAlignment::SpaceBetween).tree(),
        {200, 50}
    );

    ExpectEqual(layout.children.at(0).rect.x, 0, "space-between first x");
    ExpectEqual(layout.children.at(1).rect.x, 80, "space-between second x");
    ExpectEqual(layout.children.at(2).rect.x, 160, "space-between third x");
}

auto RowSpaceAroundDistributesFreeSpace() -> void
{
    auto layout = BuildLayout(
        Row(
            Label(L"One").maxSize({40, 20}),
            Label(L"Two").maxSize({40, 20})
        ).horizontalAlignment(MainAxisAlignment::SpaceAround).tree(),
        {200, 50}
    );

    ExpectEqual(layout.children.at(0).rect.x, 30, "space-around first x");
    ExpectEqual(layout.children.at(1).rect.x, 130, "space-around second x");
}

auto RowSpaceEvenlyDistributesFreeSpace() -> void
{
    auto layout = BuildLayout(
        Row(
            Label(L"One").maxSize({40, 20}),
            Label(L"Two").maxSize({40, 20})
        ).horizontalAlignment(MainAxisAlignment::SpaceEvenly).tree(),
        {200, 50}
    );

    ExpectEqual(layout.children.at(0).rect.x, 40, "space-evenly first x");
    ExpectEqual(layout.children.at(1).rect.x, 120, "space-evenly second x");
}

} // namespace

auto RunLayoutSpacingTests() -> void
{
    RowSpaceBetweenDistributesFreeSpace();
    RowSpaceAroundDistributesFreeSpace();
    RowSpaceEvenlyDistributesFreeSpace();
}

} // namespace Blade::Tests
