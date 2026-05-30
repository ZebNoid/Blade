#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

namespace Blade::Api {

struct WidgetType
{
    uint32_t value = 0;

    friend auto operator==(WidgetType, WidgetType) -> bool = default;
};

namespace WidgetTypes {
    inline constexpr WidgetType Unknown{0};

    inline constexpr WidgetType Window{1};
    inline constexpr WidgetType Button{2};
    inline constexpr WidgetType Label{3};
    inline constexpr WidgetType ContextArea{4};
    inline constexpr WidgetType Tray{5};
    inline constexpr WidgetType Image{6};

    inline constexpr WidgetType Menu{20};
    inline constexpr WidgetType MenuItem{21};
    inline constexpr WidgetType MenuSeparator{22};

    inline constexpr WidgetType Column{100};
    inline constexpr WidgetType Row{101};
    inline constexpr WidgetType Stack{102};

    inline constexpr WidgetType ModifierPadding{1000};
    inline constexpr WidgetType ModifierBackground{1001};
    inline constexpr WidgetType ModifierStates{1002};

    inline constexpr auto User(uint32_t value) -> WidgetType
    {
        return {10000 + value};
    }
}

} // namespace Blade::Api

template <>
struct std::hash<Blade::Api::WidgetType>
{
    auto operator()(Blade::Api::WidgetType type) const noexcept -> size_t
    {
        return std::hash<uint32_t>{}(type.value);
    }
};
