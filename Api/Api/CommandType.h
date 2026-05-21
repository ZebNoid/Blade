#pragma once

namespace Blade::Api {


enum class CommandType
{
    Create,
    Update,
    Remove,
    Attach
};


inline auto to_string(CommandType c) -> std::wstring {
    switch (c) {
    case CommandType::Create:   return L"Create";
    case CommandType::Update: return L"Update";
    case CommandType::Remove:  return L"Remove";
    case CommandType::Attach:  return L"Attach";
    default:           return L"Unknown";
    }
}

} // namespace