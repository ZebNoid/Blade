#pragma once
#include <functional>


namespace Blade {

struct ButtonCallbacks
{
    // TODO on click
    std::function<void()> click = nullptr;
};

} // namespace