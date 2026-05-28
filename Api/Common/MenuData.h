#pragma once

#include <vector>

#include "MenuTrigger.h"
#include "Types.h"

namespace Blade::Api {

struct MenuItemData
{
    Api::Id id = Api::InvalidId;
    Api::Text title;
};

struct MenuData
{
    Api::MenuTrigger trigger = Api::MenuTrigger::RightClick;
    std::vector<MenuItemData> items;
};

using ContextMenus = std::vector<MenuData>;

} // namespace Blade::Api
