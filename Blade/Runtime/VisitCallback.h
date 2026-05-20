#pragma once
#include <functional>

#include "Common/Common.h"

namespace Blade {

// using VisitCallback = std::function<void(const Api::Text&, const Api::PropertyValue&)>;

using VisitFn = void(*)(const Api::Text&, const Api::PropertyValue&);

} // namespace
