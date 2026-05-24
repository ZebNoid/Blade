#pragma once
#include <variant>

#include "Types.h"

namespace Blade::Api {


enum class Events
{
    Unknown,
    Click,
    Close,
    Resize
};

using EventResult = std::variant<
    std::monostate,
    bool,
    int,
    Api::Text
>;

struct BackendEvent
{
    Api::Id target = Api::InvalidId;
    Api::Events type = Api::Events::Unknown;
    Api::EventResult value{};
};

inline auto to_string(Events e) -> std::wstring
{
    switch (e)
    {
    case Events::Unknown: return L"Unknown";
    case Events::Click: return L"Click";
    case Events::Close: return L"Close";
    case Events::Resize: return L"Resize";
    default: return L"Unknown";
    }
}

} // namespace
