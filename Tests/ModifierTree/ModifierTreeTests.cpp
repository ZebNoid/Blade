#include "ModifierTreeTests.h"

#include "Core/Expect.h"
#include "Runtime/ModifierTree/ModifierTreeBuilder.h"
#include "Widget/Label/Label.h"
#include "Widget/Layout/Column/Column.h"
#include "Widget/Window/Window.h"

namespace Blade::Tests {

namespace {

auto RootLayoutModifierWrapsRoot() -> void
{
    auto tree = ModifierTree::Builder::Expand(
        Column(Label(L"Text")).padding(8).tree()
    );

    ExpectEqual(static_cast<int>(tree.type.value), static_cast<int>(Api::WidgetTypes::ModifierPadding.value), "root layout modifier type");
    ExpectEqual(static_cast<int>(tree.children.size()), 1, "root layout modifier child count");
    ExpectEqual(static_cast<int>(tree.children.at(0).type.value), static_cast<int>(Api::WidgetTypes::Column.value), "root layout modifier child type");
}

auto NativeRootModifierDoesNotWrapRoot() -> void
{
    auto tree = ModifierTree::Builder::Expand(
        Window(Column(Label(L"Text"))).padding(8).tree()
    );

    ExpectEqual(static_cast<int>(tree.type.value), static_cast<int>(Api::WidgetTypes::Window.value), "native root type");
    ExpectEqual(static_cast<int>(tree.children.size()), 1, "native root child count");
    ExpectEqual(static_cast<int>(tree.children.at(0).type.value), static_cast<int>(Api::WidgetTypes::Column.value), "native root child type");
}

auto ChildModifierWrapsChild() -> void
{
    auto tree = ModifierTree::Builder::Expand(
        Column(Label(L"Text").padding(8)).tree()
    );

    ExpectEqual(static_cast<int>(tree.type.value), static_cast<int>(Api::WidgetTypes::Column.value), "child modifier root type");
    ExpectEqual(static_cast<int>(tree.children.size()), 1, "child modifier root child count");
    ExpectEqual(static_cast<int>(tree.children.at(0).type.value), static_cast<int>(Api::WidgetTypes::ModifierPadding.value), "child modifier wrapper type");
}

} // namespace

auto RunModifierTreeTests() -> void
{
    RootLayoutModifierWrapsRoot();
    NativeRootModifierDoesNotWrapRoot();
    ChildModifierWrapsChild();
}

} // namespace Blade::Tests
