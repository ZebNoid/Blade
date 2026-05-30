#pragma once

#include <vector>

#include "Common/Types.h"
#include "Menu/MenuTrigger.h"
#include "Menu/Shortcut.h"

namespace Blade::Api {

struct MenuItemData
{
    Api::Id id = Api::InvalidId;
    Api::Text title;
    Api::Shortcut shortcut = Api::Shortcut::None();
    bool separator = false;
    std::vector<MenuItemData> children;
};

struct MenuData
{
    Api::MenuTrigger trigger = Api::MenuTrigger::RightClick;
    std::vector<MenuItemData> items;
};

using ContextMenus = std::vector<MenuData>;

} // namespace Blade::Api
