#include "ClassRegistry.h"

auto ClassRegistry::Init(const HINSTANCE hInstance) -> void
{
    if (s_hInstance != nullptr) return;
    s_hInstance = hInstance;
}

auto ClassRegistry::Get(const std::string& key) -> const wchar_t*
{
    const auto it = s_names.find(key);
    if (it == s_names.end()) return L"";
    return it->second.c_str();
}

auto ClassRegistry::Register(const std::string& key, const ClassDesc& desc) -> void
{
    if (s_hInstance == nullptr) return;

    // already registered
    if (s_names.contains(key)) return;

    std::wstring className = desc.name;

    WNDCLASSW wc{};
    wc.lpfnWndProc = desc.proc;
    wc.hInstance = s_hInstance;
    wc.lpszClassName = className.c_str();
    wc.hCursor = desc.cursor ? desc.cursor : LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = desc.icon;
    // COLOR_WINDOW || COLOR_HIGHLIGHTTEXT
    wc.hbrBackground = desc.background != nullptr ? desc.background : (HBRUSH)(COLOR_WINDOW);
    wc.style = desc.style;

    RegisterClassW(&wc);

    s_names[key] = std::move(className);
}
