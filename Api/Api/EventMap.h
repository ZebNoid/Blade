#pragma once
#include <unordered_map>
#include <variant>

#include "Common/Common.h"


namespace Blade::Api {


using EventCallback = std::function<void()>;

using EventMap =    std::unordered_map<Api::Text, EventCallback>;


} // namespace
