#include "LayoutStackTests.h"

#include "Core/Expect.h"
#include "Layout/LayoutTestUtils.h"
#include "Widget/Label/Label.h"
#include "Widget/Layout/Column/Column.h"
#include "Widget/Layout/Stack/Stack.h"

namespace Blade::Tests {

namespace {

auto StackOverlaysChildrenInSameContentRect() -> void
{
    auto layout = BuildLayout(
        Column(
            Stack(
                Label(L"Back"),
                Label(L"Front")
            ).padding(10)
        ).tree(),
        {200, 100}
    );

    const auto& padding = layout.children.at(0);
    const auto& stack = padding.children.at(0);
    ExpectEqual(static_cast<int>(padding.children.size()), 1, "stack wrapper child count");
    ExpectEqual(static_cast<int>(stack.children.size()), 2, "stack child count");
    ExpectEqual(stack.children.at(0).rect.x, 10, "stack first child x");
    ExpectEqual(stack.children.at(0).rect.y, 10, "stack first child y");
    ExpectEqual(stack.children.at(0).rect.width, 180, "stack first child width");
    ExpectEqual(stack.children.at(0).rect.height, 24, "stack first child height");
    ExpectEqual(stack.children.at(1).rect.x, 10, "stack second child x");
    ExpectEqual(stack.children.at(1).rect.y, 10, "stack second child y");
    ExpectEqual(stack.children.at(1).rect.width, 180, "stack second child width");
    ExpectEqual(stack.children.at(1).rect.height, 24, "stack second child height");
}

auto StackDesiredSizeUsesLargestChild() -> void
{
    auto layout = BuildLayout(
        Stack(
            Label(L"Small").maxSize({80, 16}),
            Label(L"Large").minSize({160, 40})
        ).tree(),
        {300, 300}
    );

    ExpectEqual(layout.desiredSize.width, 160, "stack desired width");
    ExpectEqual(layout.desiredSize.height, 40, "stack desired height");
}

} // namespace

auto RunLayoutStackTests() -> void
{
    StackOverlaysChildrenInSameContentRect();
    StackDesiredSizeUsesLargestChild();
}

} // namespace Blade::Tests
