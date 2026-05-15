#pragma once

#include <vector>
#include <memory>

#include "../../Widget/Widget.h"

class Container : public Widget
{

protected:
    std::vector<std::unique_ptr<Widget>> m_children;
};
