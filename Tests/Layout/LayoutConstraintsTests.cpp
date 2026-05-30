#include "LayoutConstraintsTests.h"

#include "Core/Expect.h"
#include "Layout/LayoutTestUtils.h"
#include "Widget/Label/Label.h"
#include "Widget/Layout/Column/Column.h"
#include "Widget/Layout/Row/Row.h"

namespace Blade::Tests {

namespace {

auto MinSizeExpandsDesiredSize() -> void
{
    auto layout = BuildLayout(
        Column(
            Label(L"Text")
                .minSize({160, 40})
        ).tree(),
        {300, 300}
    );

    const auto& label = layout.children.at(0);
    ExpectEqual(label.desiredSize.width, 160, "min desired width");
    ExpectEqual(label.desiredSize.height, 40, "min desired height");
}

auto MaxSizeClampsDesiredSize() -> void
{
    auto layout = BuildLayout(
        Column(
            Label(L"Text")
                .maxSize({80, 12})
        ).tree(),
        {300, 300}
    );

    const auto& label = layout.children.at(0);
    ExpectEqual(label.desiredSize.width, 80, "max desired width");
    ExpectEqual(label.desiredSize.height, 12, "max desired height");
}

auto MaxSizeAffectsSiblingLayout() -> void
{
    auto layout = BuildLayout(
        Row(
            Label(L"Left").maxSize({80, 0}),
            Label(L"Right")
        ).tree(),
        {300, 100}
    );

    ExpectEqual(layout.children.at(0).rect.width, 80, "left rect width");
    ExpectEqual(layout.children.at(1).rect.x, 80, "right rect x");
}

auto MinMaxSizeAffectsFlexLayout() -> void
{
    auto layout = BuildLayout(
        Row(
            Label(L"Min").flex(1).minSize({120, 0}),
            Label(L"Flex").flex(1)
        ).tree(),
        {300, 100}
    );

    ExpectEqual(layout.children.at(0).desiredSize.width, 120, "min flex desired width");
    ExpectEqual(layout.children.at(0).rect.width, 150, "min flex rect width");
    ExpectEqual(layout.children.at(1).rect.x, 150, "second flex rect x");
    ExpectEqual(layout.children.at(1).rect.width, 150, "second flex rect width");
}

} // namespace

auto RunLayoutConstraintsTests() -> void
{
    MinSizeExpandsDesiredSize();
    MaxSizeClampsDesiredSize();
    MaxSizeAffectsSiblingLayout();
    MinMaxSizeAffectsFlexLayout();
}

} // namespace Blade::Tests
