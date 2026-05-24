#include "NativeButtonProps.h"

#include "WinApi/NativeApi/NativeApi.h"


namespace Blade::Backend {

namespace {

auto ApplyIsDefault(HWND hwnd, const Api::PropertyMap& propertyMap) -> void
{
    const auto it = propertyMap.find(Api::Props::IsDefault);

    if (it == propertyMap.end())
    {
        return;
    }

    const auto* isDefault = std::get_if<bool>(&it->second);

    if (!isDefault)
    {
        return;
    }

    const auto style = *isDefault ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON;
    NativeApi::SetStyle(hwnd, style, TRUE);
}

} // namespace

auto NativeButtonProps::Apply(HWND hwnd, const Api::PropertyMap& propertyMap) -> void
{
    ApplyIsDefault(hwnd, propertyMap);
}

} // namespace Blade::Backend
