#include "Core/TestRunner.h"
#include "Layout/LayoutAlignmentTests.h"
#include "Layout/LayoutConstraintsTests.h"
#include "Layout/LayoutFlexTests.h"
#include "Layout/LayoutPaddingTests.h"
#include "Layout/LayoutRootModifierTests.h"
#include "Layout/LayoutSpacingTests.h"
#include "Layout/LayoutStackTests.h"
#include "ModifierTree/ModifierTreeTests.h"

auto main() -> int
{
    Blade::Tests::TestRunner runner;

    runner.Run("Layout alignment", Blade::Tests::RunLayoutAlignmentTests);
    runner.Run("Layout constraints", Blade::Tests::RunLayoutConstraintsTests);
    runner.Run("Layout flex", Blade::Tests::RunLayoutFlexTests);
    runner.Run("Layout padding", Blade::Tests::RunLayoutPaddingTests);
    runner.Run("Layout root modifiers", Blade::Tests::RunLayoutRootModifierTests);
    runner.Run("Layout spacing", Blade::Tests::RunLayoutSpacingTests);
    runner.Run("Layout stack", Blade::Tests::RunLayoutStackTests);
    runner.Run("Modifier tree", Blade::Tests::RunModifierTreeTests);

    return runner.Result();
}
