#pragma once

#include "Runtime/LayoutEngine/Data/LayoutContext.h"

namespace Blade::Layout::Virtual {

auto Measure(LayoutContext& ctx) -> Api::Size;
auto Arrange(LayoutContext& ctx) -> void;

} // namespace Blade::Layout::Virtual
