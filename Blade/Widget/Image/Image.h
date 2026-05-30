#pragma once

#include "Base/Widget.h"
#include "ImageProps.h"
#include "Runtime/Normalize/Normalize.h"

namespace Blade {

class Image : public Widget<Image>
{
public:
    explicit Image(Api::Text source)
    {
        m_tree.type = Api::WidgetTypes::Image;
        Normalize::PropsMerge(m_tree, ImageProps{});
        m_tree.backend.create[Api::Props::Source] = std::move(source);
    }

    auto set(ImageProps props) -> Image&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto source(Api::Text value) -> Image&
    {
        m_tree.backend.create[Api::Props::Source] = std::move(value);
        return *this;
    }
};

} // namespace Blade
