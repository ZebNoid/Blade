#pragma once

#include "Common/Types.h"

namespace Blade::Api {

enum class KeyModifier
{
    None = 0,
    Ctrl = 1 << 0,
    Alt = 1 << 1,
    Shift = 1 << 2
};

inline auto operator|(KeyModifier left, KeyModifier right) -> KeyModifier
{
    return static_cast<KeyModifier>(static_cast<int>(left) | static_cast<int>(right));
}

inline auto Has(KeyModifier value, KeyModifier flag) -> bool
{
    return (static_cast<int>(value) & static_cast<int>(flag)) != 0;
}

struct Shortcut
{
    wchar_t key{};
    KeyModifier modifiers = KeyModifier::None;

    static auto None() -> Shortcut { return {}; }
    static auto Ctrl(wchar_t key) -> Shortcut { return { .key = key, .modifiers = KeyModifier::Ctrl }; }
    static auto Alt(wchar_t key) -> Shortcut { return { .key = key, .modifiers = KeyModifier::Alt }; }
    static auto Shift(wchar_t key) -> Shortcut { return { .key = key, .modifiers = KeyModifier::Shift }; }
};

inline auto IsNone(const Shortcut& shortcut) -> bool
{
    return shortcut.key == 0;
}

} // namespace Blade::Api
