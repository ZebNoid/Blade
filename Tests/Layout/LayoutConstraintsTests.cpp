#include "LayoutConstraintsTests.h"

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

} // namespace

auto RunLayoutConstraintsTests() -> void
{
    MinSizeExpandsDesiredSize();
    MaxSizeClampsDesiredSize();
    MaxSizeAffectsSiblingLayout();
}

} // namespace Blade::Tests
