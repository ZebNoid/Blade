#pragma once

#include "Widget/ComponentType.h"

namespace Blade::Backend::UI {

inline constexpr auto Window = Api::ComponentTypes::Window;
inline constexpr auto Button = Api::ComponentTypes::Button;
inline constexpr auto ButtonCustom = Api::ComponentTypes::Backend(1);
inline constexpr auto Label = Api::ComponentTypes::Label;
inline constexpr auto ContextArea = Api::ComponentTypes::ContextArea;
inline constexpr auto Tray = Api::ComponentTypes::Tray;

} // namespace Blade::Backend::UI
