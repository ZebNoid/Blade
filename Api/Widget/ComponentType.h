#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

namespace Blade::Api {

struct ComponentType
{
    uint32_t value = 0;

    friend auto operator==(ComponentType, ComponentType) -> bool = default;
};

namespace ComponentTypes {
    inline constexpr ComponentType Unknown{0};

    inline constexpr ComponentType Window{1};
    inline constexpr ComponentType Tray{2};

    inline constexpr ComponentType Button{100};
    inline constexpr ComponentType Label{101};
    inline constexpr ComponentType ContextArea{102};

    inline constexpr ComponentType Surface{200};
    inline constexpr ComponentType LabelSurface{201};
    inline constexpr ComponentType ImageSurface{202};

    inline constexpr auto Backend(uint32_t value) -> ComponentType
    {
        return {50000 + value};
    }

    inline constexpr auto User(uint32_t value) -> ComponentType
    {
        return {100000 + value};
    }
}

} // namespace Blade::Api

template <>
struct std::hash<Blade::Api::ComponentType>
{
    auto operator()(Blade::Api::ComponentType type) const noexcept -> size_t
    {
        return std::hash<uint32_t>{}(type.value);
    }
};
