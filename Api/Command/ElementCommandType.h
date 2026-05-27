#pragma once


namespace Blade::Api {

enum class ElementCommandType
{
    Create,
    Update,
    Remove,
    Attach
};

inline auto to_string(ElementCommandType c) -> std::wstring
{
    switch (c)
    {
    case ElementCommandType::Create: return L"Create";
    case ElementCommandType::Update: return L"Update";
    case ElementCommandType::Remove: return L"Remove";
    case ElementCommandType::Attach: return L"Attach";
    default: return L"Unknown";
    }
}

} // namespace Blade::Api
