#include "Layout/LayoutAlignmentTests.h"
#include "Layout/LayoutConstraintsTests.h"
#include "Layout/LayoutFlexTests.h"
#include "Layout/LayoutPaddingTests.h"
#include "Layout/LayoutRootModifierTests.h"
#include "Layout/LayoutSpacingTests.h"
#include "Layout/LayoutStackTests.h"

#include <exception>
#include <iostream>

auto main() -> int
{
    try
    {
        Blade::Tests::RunLayoutAlignmentTests();
        Blade::Tests::RunLayoutConstraintsTests();
        Blade::Tests::RunLayoutFlexTests();
        Blade::Tests::RunLayoutPaddingTests();
        Blade::Tests::RunLayoutRootModifierTests();
        Blade::Tests::RunLayoutSpacingTests();
        Blade::Tests::RunLayoutStackTests();
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
