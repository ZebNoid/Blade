#pragma once

namespace Blade::Api {

enum class MenuTrigger
{
    None = 0,
    LeftClick = 1 << 0,
    MiddleClick = 1 << 1,
    RightClick = 1 << 2
};

inline auto operator|(MenuTrigger left, MenuTrigger right) -> MenuTrigger
{
    return static_cast<MenuTrigger>(static_cast<int>(left) | static_cast<int>(right));
}

inline auto operator&(MenuTrigger left, MenuTrigger right) -> MenuTrigger
{
    return static_cast<MenuTrigger>(static_cast<int>(left) & static_cast<int>(right));
}

inline auto Has(MenuTrigger value, MenuTrigger flag) -> bool
{
    return (static_cast<int>(value) & static_cast<int>(flag)) != 0;
}

} // namespace Blade::Api
