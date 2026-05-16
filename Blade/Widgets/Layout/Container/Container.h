#pragma once

#include <memory>
#include <vector>

#include "Widgets/Widget/Widget.h"


namespace Blade {

class Container : public Widget
{

protected:
    std::vector<std::unique_ptr<Widget>> m_children;
};


} // namespace
