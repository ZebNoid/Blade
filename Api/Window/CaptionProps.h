#pragma once

namespace Blade::Api {

enum class CaptionButton
{
    None = 0,
    Min = 1 << 0,
    Max = 1 << 1,
    Close = 1 << 2,
    All = Min | Max | Close
};

inline auto operator|(CaptionButton left, CaptionButton right) -> CaptionButton
{
    return static_cast<CaptionButton>(static_cast<int>(left) | static_cast<int>(right));
}

struct CaptionProps
{
    bool visible = true;
    CaptionButton buttons = CaptionButton::All;
};

} // namespace Blade::Api
