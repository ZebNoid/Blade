#include "NativeButtonProps.h"

#include "NativeButtonApi/NativeButtonApi.h"
#include "Property/PropertyReader.h"


namespace Blade::Backend {

namespace {

auto ApplyIsDefault(HWND hwnd, const Api::PropertyMap& propertyMap) -> void
{
    const auto* isDefault = PropertyReader::Get<bool>(propertyMap, Api::Props::IsDefault);
    if (!isDefault) return;

    // TODO fix *isDefault is always false, no data from blade?
    const auto style = *isDefault ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON;
    NativeButtonApi::SetStyle(hwnd, style, TRUE);
}

} // namespace

auto NativeButtonProps::Apply(HWND hwnd, const Api::PropertyMap& propertyMap) -> void
{
    ApplyIsDefault(hwnd, propertyMap);
}

} // namespace Blade::Backend
