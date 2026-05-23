#pragma once
#include <utility>

#include "Common/Property.h"
#include "Runtime/LayoutEngine/Data/LayoutData.h"


namespace Blade {

struct BackendProps
{
    Api::PropertyMap create;

    auto merge(
        BackendProps&& other
    ) -> void
    {
        for (auto& [key, value] : other.create)
        {
            create.insert_or_assign(key, std::move(value));
        }
    }
};

struct NormalizedProps
{
    BackendProps backend;

    LayoutData layout;
    bool hasLayout = false;
    bool hasSize = false;
    bool hasPosition = false;
    bool hasGap = false;

    auto applyTo(
        LayoutData& target
    ) const -> void
    {
        if (hasLayout)
        {
            target.box = layout.box;
        }

        if (hasSize)
        {
            target.size = layout.size;
        }

        if (hasPosition)
        {
            target.position = layout.position;
        }

        if (hasGap)
        {
            target.gap = layout.gap;
        }
    }
};

} // namespace Blade
