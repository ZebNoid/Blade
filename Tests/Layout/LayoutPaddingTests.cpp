#include "LayoutPaddingTests.h"

#include <stdexcept>
#include <string>

#include "Runtime/LayoutRuntime/LayoutPass/LayoutPass.h"
#include "Runtime/ModifierTree/ModifierTreeBuilder.h"
#include "Widget/Label/Label.h"
#include "Widget/Layout/Column/Column.h"

namespace Blade::Tests {

namespace {

auto ExpectEqual(int actual, int expected, const char* name) -> void
{
    if (actual == expected) return;
    throw std::runtime_error(std::string(name) + ": expected " + std::to_string(expected) + ", actual " + std::to_string(actual));
}

auto BuildLayout(WidgetTree tree, Api::Size available) -> LayoutNode
{
    return LayoutPass::Compute(ModifierTreeBuilder::Expand(std::move(tree)), available);
}

auto PaddingChangesChildRect() -> void
{
    auto layout = BuildLayout(
        Blade::Column(
            Blade::Label(L"Text").padding(16)
        ).tree(),
        {200, 200}
    );

    const auto& padding = layout.children.at(0);
    const auto& label = padding.children.at(0);

    ExpectEqual(padding.desiredSize.width, 152, "padding.desiredSize.width");
    ExpectEqual(padding.desiredSize.height, 56, "padding.desiredSize.height");
    ExpectEqual(label.rect.x, 16, "label.rect.x");
    ExpectEqual(label.rect.y, 16, "label.rect.y");
    ExpectEqual(label.rect.width, 168, "label.rect.width");
    ExpectEqual(label.rect.height, 24, "label.rect.height");
}

auto PaddingKeepsChildFlex() -> void
{
    auto layout = BuildLayout(
        Blade::Column(
            Blade::Label(L"Text").flex(1).padding(16),
            Blade::Label(L"Bottom")
        ).tree(),
        {200, 200}
    );

    const auto& padding = layout.children.at(0);
    const auto& label = padding.children.at(0);

    ExpectEqual(padding.rect.height, 176, "padding.rect.height");
    ExpectEqual(label.rect.y, 16, "label.rect.y");
    ExpectEqual(label.rect.height, 144, "label.rect.height");
}

} // namespace

auto RunLayoutPaddingTests() -> void
{
    PaddingChangesChildRect();
    PaddingKeepsChildFlex();
}

} // namespace Blade::Tests
