#include "LayoutRootModifierTests.h"

#include "Core/Expect.h"
#include "Layout/LayoutTestUtils.h"
#include "Widget/Label/Label.h"
#include "Widget/Layout/Column/Column.h"

namespace Blade::Tests {

namespace {

auto RootLayoutPaddingAffectsChildRect() -> void
{
    auto layout = BuildLayout(
        Column(
            Label(L"Text")
        ).padding(12).tree(),
        {200, 100}
    );

    const auto& column = layout.children.at(0);
    const auto& label = column.children.at(0);

    ExpectEqual(label.rect.x, 12, "root padding label x");
    ExpectEqual(label.rect.y, 12, "root padding label y");
    ExpectEqual(label.rect.width, 176, "root padding label width");
}

} // namespace

auto RunLayoutRootModifierTests() -> void
{
    RootLayoutPaddingAffectsChildRect();
}

} // namespace Blade::Tests
