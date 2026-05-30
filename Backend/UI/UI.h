#pragma once

#include "Widget/ComponentType.h"

namespace Blade::Backend::UI {

inline constexpr auto Window = Api::ComponentTypes::Window;
inline constexpr auto Button = Api::ComponentTypes::Button;
inline constexpr auto Label = Api::ComponentTypes::LabelSurface;
inline constexpr auto LabelNative = Api::ComponentTypes::Label;
inline constexpr auto LabelSurface = Api::ComponentTypes::LabelSurface;
inline constexpr auto Tray = Api::ComponentTypes::Tray;
inline constexpr auto Surface = Api::ComponentTypes::Surface;

} // namespace Blade::Backend::UI
