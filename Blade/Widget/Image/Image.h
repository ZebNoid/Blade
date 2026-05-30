#pragma once

#include "Base/Widget.h"

namespace Blade {

class Image : public Widget<Image>
{
public:
    explicit Image(Api::Text source)
    {
        m_tree.type = Api::WidgetTypes::Image;
        size({120, 120});
        m_tree.backend.create[Api::Props::Source] = std::move(source);
    }

    auto source(Api::Text value) -> Image&
    {
        m_tree.backend.create[Api::Props::Source] = std::move(value);
        return *this;
    }
};

} // namespace Blade
