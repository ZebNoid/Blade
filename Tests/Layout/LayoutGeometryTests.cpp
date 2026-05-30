#include "LayoutGeometryTests.h"

#include "Core/Expect.h"
#include "Runtime/LayoutEngine/Geometry/LayoutAxis.h"
#include "Runtime/LayoutEngine/Geometry/LayoutGeometry.h"

namespace Blade::Tests {

namespace {

auto GeometryInflatesAndDeflates() -> void
{
    const Api::Thickness thickness{4, 6, 8, 10};

    const auto inflated = Layout::Geometry::Inflate({100, 50}, thickness);
    ExpectEqual(inflated.width, 112, "inflated width");
    ExpectEqual(inflated.height, 66, "inflated height");

    const auto deflated = Layout::Geometry::Deflate({10, 20, 100, 50}, thickness);
    ExpectEqual(deflated.x, 14, "deflated x");
    ExpectEqual(deflated.y, 26, "deflated y");
    ExpectEqual(deflated.width, 88, "deflated width");
    ExpectEqual(deflated.height, 34, "deflated height");
}

auto GeometryDeflateClampsToZero() -> void
{
    const auto rect = Layout::Geometry::Deflate({0, 0, 10, 10}, {8});

    ExpectEqual(rect.width, 0, "deflated clamped width");
    ExpectEqual(rect.height, 0, "deflated clamped height");
}

auto GeometryConstrainsSize() -> void
{
    const auto minOnly = Layout::Geometry::Constrain({50, 20}, {80, 40}, {});
    ExpectEqual(minOnly.width, 80, "min constrained width");
    ExpectEqual(minOnly.height, 40, "min constrained height");

    const auto maxOnly = Layout::Geometry::Constrain({120, 90}, {}, {100, 60});
    ExpectEqual(maxOnly.width, 100, "max constrained width");
    ExpectEqual(maxOnly.height, 60, "max constrained height");
}

auto AxisMapsHorizontalAndVertical() -> void
{
    const Api::Size size{100, 40};
    const Api::Rect rect{10, 20, 300, 120};

    ExpectEqual(Layout::Axis::MainSize(LayoutAxis::Horizontal, size), 100, "horizontal main size");
    ExpectEqual(Layout::Axis::CrossSize(LayoutAxis::Horizontal, size), 40, "horizontal cross size");
    ExpectEqual(Layout::Axis::MainSize(LayoutAxis::Vertical, size), 40, "vertical main size");
    ExpectEqual(Layout::Axis::CrossSize(LayoutAxis::Vertical, size), 100, "vertical cross size");

    ExpectEqual(Layout::Axis::MainRectPosition(LayoutAxis::Horizontal, rect), 10, "horizontal main position");
    ExpectEqual(Layout::Axis::CrossRectPosition(LayoutAxis::Horizontal, rect), 20, "horizontal cross position");
    ExpectEqual(Layout::Axis::MainRectPosition(LayoutAxis::Vertical, rect), 20, "vertical main position");
    ExpectEqual(Layout::Axis::CrossRectPosition(LayoutAxis::Vertical, rect), 10, "vertical cross position");
}

auto MainAxisSpacingIsCalculated() -> void
{
    ExpectEqual(Layout::Geometry::MainAxisOffset(MainAxisAlignment::Center, 200, 100, 2), 50, "center offset");
    ExpectEqual(Layout::Geometry::MainAxisOffset(MainAxisAlignment::End, 200, 100, 2), 100, "end offset");
    ExpectEqual(Layout::Geometry::MainAxisOffset(MainAxisAlignment::SpaceAround, 200, 100, 2), 25, "space-around offset");
    ExpectEqual(Layout::Geometry::MainAxisOffset(MainAxisAlignment::SpaceEvenly, 200, 100, 2), 33, "space-evenly offset");

    ExpectEqual(Layout::Geometry::MainAxisGap(MainAxisAlignment::SpaceBetween, 4, 200, 100, 3), 54, "space-between gap");
    ExpectEqual(Layout::Geometry::MainAxisGap(MainAxisAlignment::SpaceAround, 4, 200, 100, 2), 54, "space-around gap");
    ExpectEqual(Layout::Geometry::MainAxisGap(MainAxisAlignment::SpaceEvenly, 4, 200, 100, 2), 37, "space-evenly gap");
}

} // namespace

auto RunLayoutGeometryTests() -> void
{
    GeometryInflatesAndDeflates();
    GeometryDeflateClampsToZero();
    GeometryConstrainsSize();
    AxisMapsHorizontalAndVertical();
    MainAxisSpacingIsCalculated();
}

} // namespace Blade::Tests
