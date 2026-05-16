#pragma once

#include <memory>
#include <vector>

#include "Widgets/Widget/Widget.h"


namespace Blade {

class Container : public Widget
{

public:
    auto children() -> const std::vector<std::unique_ptr<Widget>>& override
    {
        return m_children;
    }

protected:
    std::vector<std::unique_ptr<Widget>> m_children;
};


} // namespace
