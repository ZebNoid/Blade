#include "Layout/LayoutAlignmentTests.h"
#include "Layout/LayoutPaddingTests.h"

#include <exception>
#include <iostream>

auto main() -> int
{
    try
    {
        Blade::Tests::RunLayoutAlignmentTests();
        Blade::Tests::RunLayoutPaddingTests();
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
