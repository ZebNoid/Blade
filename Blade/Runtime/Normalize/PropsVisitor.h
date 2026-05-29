#pragma once
#include <utility>

#include "Common/LayoutProps.h"
#include "Common/Property.h"
#include "Props/LayoutProps/CrossAxisAlignment.h"
#include "Props/LayoutProps/MainAxisAlignment.h"
#include "Runtime/Normalize/NormalizedProps.h"


namespace Blade {

class PropsVisitor
{
public:
    auto set(
        const Api::Props& prop,
        const Api::PropertyValue& value
    ) -> void
    {
        switch (prop)
        {
        case Api::Props::Size:
            if (const auto* size =
                    std::get_if<Api::Size>(&value))
            {
                m_props.layout.size = *size;
                m_props.hasSize = true;
            }
            break;

        case Api::Props::Position:
            if (const auto* position =
                    std::get_if<Api::Point>(&value))
            {
                m_props.layout.position = *position;
                m_props.hasPosition = true;
            }
            break;

        case Api::Props::Gap:
            if (const auto* gap =
                    std::get_if<int>(&value))
            {
                m_props.layout.gap = *gap;
                m_props.hasGap = true;
            }
            break;

        case Api::Props::Title:
        case Api::Props::IsDefault:
            m_props.backend.create[prop] = value;
            break;

        default:
            m_props.backend.create[prop] = value;
            break;
        }
    }

    auto set(const Api::Props& prop, const Api::LayoutProps& value) -> void
    {
        if (prop != Api::Props::Layout) return;

        m_props.layout.box = value;
        m_props.hasLayout = true;
    }

    auto set(
        const MainAxisAlignment alignment
    ) -> void
    {
        m_props.layout.mainAxisAlignment = alignment;
        m_props.hasMainAxisAlignment = true;
    }

    auto set(
        const CrossAxisAlignment alignment
    ) -> void
    {
        m_props.layout.crossAxisAlignment = alignment;
        m_props.hasCrossAxisAlignment = true;
    }

    auto take() -> NormalizedProps
    {
        return std::move(m_props);
    }

private:
    NormalizedProps m_props;
};

} // namespace
